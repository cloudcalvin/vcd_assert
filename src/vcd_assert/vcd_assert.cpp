#include "vcd_assert/actions.hpp"
#include "vcd_assert/timing_checker.hpp"
#include "vcd_assert/sdf_matching.hpp"

#include "vcd/actions/header.hpp"
#include "vcd/grammar/grammar.hpp"
#include "vcd/types/header_reader.hpp"

#include <sdf/actions/base.hpp>
#include <sdf/grammar/base.hpp>
#include <sdf/types/base.hpp>

#include <verilog/ieee1364_2001/actions/grammar.hpp>
#include <verilog/ieee1364_2001/actions/module.hpp>
#include <verilog/ieee1364_2001/grammar/grammar.hpp>
#include <verilog/ieee1364_2001/grammar/module.hpp>
#include <verilog/types/commands.hpp>
#include <verilog/types/design_reader.hpp>
#include <verilog/types/module.hpp>

#include <parse/actions/control.hpp>
#include <parse/actions/make_pegtl_template.hpp>
#include <parse/util/filesystem.hpp>

#include <tao/pegtl/file_input.hpp>
#include <tao/pegtl/memory_input.hpp>
#include <tao/pegtl/parse.hpp>

#include <CLI/CLI.hpp>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <iostream>
#include <range/v3/algorithm/reverse.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/zip.hpp>
#include <string_view>

// #include <range/v3/view/foreach.hpp>
// #include <range/v3/algorithm/remove_if.hpp>

namespace fs = Parse::Util::fs;
namespace rsv = ranges::view;

struct NodeApply {
  std::string node;
  std::vector<std::string> sdf_files;
};

int main(int argc, char **argv)
{
  CLI::App cli("VCDAssert: Post processing VCD files for timing violations");
  cli.failure_message(CLI::FailureMessage::help);

  std::string vcd_file;
  auto vcd_file_option = cli.add_option("vcd_file", vcd_file, "VCD file");
  vcd_file_option->required();
  vcd_file_option->check(CLI::ExistingFile);

  std::string top_module;
  cli.add_option("--top,-t", top_module, "Name of top verilog module");

  std::vector<std::string> source_files;
  cli.add_option("--include,-i", source_files, "Verilog Source Files");

  std::vector<std::string> vcd_nodes;
  auto node_option = cli.add_option("--node,-n", vcd_nodes, "VCD Node");

  std::vector<std::string> sdf_files;
  auto sdf_option = cli.add_option("--sdf,-s", sdf_files, "SDF File to apply");

  int verbose;
  cli.add_flag("--verbose,-v", verbose, "Verbosity level [1-3]");

  CLI11_PARSE(cli, argc, argv);

  ranges::reverse(vcd_nodes);
  ranges::reverse(sdf_files);
  // TODO : why reverse? Should I reverse verilog files?

  // Condense vcd_nodes and sdf_files into apply_nodes
  // TODO look into lambda api of CLI11
  std::vector<NodeApply> apply_nodes;
  for (auto option : cli.parse_order()) {
    if (option == node_option) {
      auto cur_node = vcd_nodes.back();
      vcd_nodes.pop_back();

      if (!apply_nodes.empty() && apply_nodes.back().sdf_files.empty()) {
        fmt::print(
            FMT_STRING(
                "WARNING: Node without files matched to it. (Node={})\n"),
            apply_nodes.back().node);
        apply_nodes.back().node = cur_node;
      } else {
        apply_nodes.push_back(NodeApply{cur_node, {}});
      }
    }

    if (option == sdf_option) {
      auto cur_sdf = sdf_files.back();
      sdf_files.pop_back();

      if (apply_nodes.empty())
        apply_nodes.push_back({".", {}});

      apply_nodes.back().sdf_files.push_back(cur_sdf);
    }
  }

  if (!apply_nodes.empty() && apply_nodes.back().sdf_files.empty()) {
    fmt::print(
        FMT_STRING("WARNING: Node without files matched to it. (Node:{})\n"),
        apply_nodes.back().node);
    apply_nodes.pop_back();
  }

  if (apply_nodes.empty()) {
    fmt::print(FMT_STRING("ERROR: No timing checks to match!\n"));
    // return 1;
  }

  assert(sdf_files.empty());
  assert(vcd_nodes.empty());

  // Initialise the Verilog design reader
  Verilog::DesignReader design_reader{};

  Verilog::Util::InputMap inputmap{};

  // Find file containing top module and populate input map.
  std::optional<std::size_t> starting_source_file_index_op{};

  for (auto &&[i, file] : rsv::zip(rsv::indices, source_files)) {
    if (fs::exists(file)) {
      // auto file_path_normal = fs::path(file).lexically_normal();
      auto abs_path = fs::canonical(file);

      tao::pegtl::file_input<> input(abs_path);

      Verilog::IEEE1364_2001::Actions::ModuleEvent me{};

      // Parse with only Module actions, to build module map.
      auto result = tao::pegtl::parse<
          Verilog::IEEE1364_2001::Grammar::_grammar_,
          Parse::make_pegtl_template<
              Verilog::IEEE1364_2001::Actions::ModuleDescriptionAction>::type,
          Parse::capture_control>(input, me);

      if (!result) {
        fmt::print(FMT_STRING("ERROR: Failed to parse Verilog file:\n"));
      } else {
        if (me.module_identifier == top_module) {
          starting_source_file_index_op = (std::size_t)i;
        }
      }
    } else {
      fmt::print("ERROR: file not found : {}\n", file);
    }
  }

  if (!source_files.empty()) {

    if (starting_source_file_index_op.has_value()) {
      auto index = starting_source_file_index_op.value();

      auto top_file_normal =
          fs::path(source_files[index]); //.lexically_normal();
      auto top_file_abs_path = fs::canonical(top_file_normal);

      for (auto &&file : source_files) {

        // auto file_path_normal = fs::path(file).lexically_normal();
        // auto abs_path = fs::weakly_canonical(file_path_normal);

        // auto rel_to_top_file_path = fs::relative(
        //     fs::path(abs_path), fs::path(top_file_abs_path).parent_path());

        auto abs_path = fs::canonical(fs::path(file));

        // TODO search in 'include statement' apply action, not here..
        inputmap.emplace(abs_path, // relative path from the test bench
                         Verilog::Util::ParseInput{
                             Verilog::Util::InputTypeEnum::file, abs_path});
      }

      // Parse starting from top Verilog file
      tao::pegtl::file_input<> verilog_input(source_files[index]);

      // Parse Verilog from top
      auto result = tao::pegtl::parse<
          Verilog::IEEE1364_2001::Grammar::_grammar_,
          Parse::make_pegtl_template<
              Verilog::IEEE1364_2001::Actions::GrammarAction>::type,
          Parse::capture_control>(verilog_input, design_reader, inputmap);

      if (!result) {
        throw std::runtime_error(
            "ERROR: Unsuccessful parse of Verilog source file!\n");
      }

    } else {
      throw std::runtime_error("ERROR: Cannot find indicated top module!\n");
    }
  } else {
    // TODO : optional or mandatory?
    fmt::print(FMT_STRING("WARN: No verilog files supplied for parsing\n"));
  }

  // Finalize verilog parsing into Design object.
  auto design_p = design_reader.release();
  assert(design_p.operator bool());

  // Read in the VCD file header
  VCD::HeaderReader vcd_reader{};
  tao::pegtl::file_input<> vcd_input(vcd_file);
  tao::pegtl::parse<
      VCD::Grammar::header_commands,
      Parse::make_pegtl_template<VCD::Actions::HeaderAction>::type,
      Parse::capture_control>(vcd_input, vcd_reader);

  auto header_p = std::make_shared<VCD::Header>(vcd_reader.release());

  // Initialise the timing checker ( applies Verilog SDFs in constructor )
  auto timing_checker = VCDAssert::TimingChecker(header_p, std::move(design_p));

  // Read in and apply the SDF files for each node supplied on COMMAND LINE
  for (auto &&[node, sdf_file_array] : apply_nodes) {

    SDF::HierarchicalIdentifier path{};

    // if the node specifed on CMD is a path, parse it, even if single
    // identifier.
    tao::pegtl::memory_input<> path_input(node, "node");
    tao::pegtl::parse<SDF::Grammar::hierarchical_identifier,
                      Parse::make_pegtl_template<
                          SDF::Actions::HierarchicalIdentifierAction>::type,
                      Parse::capture_control>(path_input, path);

    for (auto &&sdf_file : sdf_file_array) {

      auto node_scope_index_op = VCDAssert::match_scope(*header_p, path.value, 0);

      if (node_scope_index_op.has_value()) {
        timing_checker.apply_sdf_file(sdf_file,
                                      node_scope_index_op.value());
      } else {
        // could not find the supplied scope.
      }
    }
  }

  // Stream in vcd file
  tao::pegtl::parse<
      Parse::Grammar::star<VCD::Grammar::simulation_command>,
      Parse::make_pegtl_template<VCDAssert::TimingCheckerAction>::type,
      Parse::capture_control>(vcd_input, timing_checker);

  return 0;
}
