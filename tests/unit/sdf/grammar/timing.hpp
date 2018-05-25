#ifndef LIBSDF_TEST_SDF_TIMING_H
#define LIBSDF_TEST_SDF_TIMING_H

#include "./base.hpp"
#include <sdf/grammar/values.h>

namespace Test {
namespace SDF {
namespace Grammar {

using namespace Parse::Test;
using namespace SDF::Grammar;

constexpr auto sdf_cell_ex1=
R"((CELL 
    (CELLTYPE "CDS_GEN_FD_P_SD_RB_SB_NO")
    (INSTANCE top.ff1)
)
)";

auto constexpr const timing_spec_str =               R"(test)";
auto constexpr const del_spec_str =                  R"(test)";
auto constexpr const tc_spec_str =                   R"(test)";
auto constexpr const te_spec_str =                   R"(test)";
auto constexpr const lbl_spec_str =                  R"(test)";
auto constexpr const deltype_str =                   R"(test)";
auto constexpr const pathpulse_deltype_str =         R"(test)";
auto constexpr const pathpulsepercent_deltype_str =  R"(test)";
auto constexpr const absolute_deltype_str =          R"(test)";
auto constexpr const increment_deltype_str =         R"(test)";
auto constexpr const input_output_path_str =         R"(test)";
auto constexpr const del_def_str =                   R"(test)";
auto constexpr const iopath_def_str =                R"(test)";
auto constexpr const retain_def_str =                R"(test)";
auto constexpr const cond_def_str =                  R"(test)";
auto constexpr const condelse_def_str =              R"(test)";
auto constexpr const port_def_str =                  R"(test)";
auto constexpr const interconnect_def_str =          R"(test)";
auto constexpr const netdelay_def_str =              R"(test)";
auto constexpr const device_def_str =                R"(test)";
auto constexpr const tchk_def_str =                  R"(test)";
auto constexpr const setup_timing_check_str =        R"(test)";
auto constexpr const hold_timing_check_str =         R"(test)";
auto constexpr const setuphold_timing_check_str =    R"(test)";
auto constexpr const recovery_timing_check_str =     R"(test)";
auto constexpr const removal_timing_check_str =      R"(test)";
auto constexpr const recrem_timing_check_str =       R"(test)";
auto constexpr const skew_timing_check_str =         R"(test)";
auto constexpr const bidirectskew_timing_check_str = R"(test)";
auto constexpr const width_timing_check_str =        R"(test)";
auto constexpr const period_timing_check_str =       R"(test)";
auto constexpr const nochange_timing_check_str =     R"(test)";
auto constexpr const port_tchk_str =                 R"(test)";
auto constexpr const scond_str =                     R"(test)";
auto constexpr const ccond_str =                     R"(test)";
auto constexpr const te_def_str =                    R"(test)";
auto constexpr const cns_def_str =                   R"(test)";
auto constexpr const path_constraint_str =           R"(test)";
auto constexpr const period_constraint_str =         R"(test)";
auto constexpr const sum_constraint_str =            R"(test)";
auto constexpr const diff_constraint_str =           R"(test)";
auto constexpr const skew_constraint_str =           R"(test)";
auto constexpr const exception_str =                 R"(test)";
auto constexpr const name_str =                      R"(test)";
auto constexpr const constraint_path_str =           R"(test)";
auto constexpr const tenv_def_str =                  R"(test)";
auto constexpr const arrival_env_str =               R"(test)";
auto constexpr const departure_env_str =             R"(test)";
auto constexpr const slack_env_str =                 R"(test)";
auto constexpr const waveform_env_str =              R"(test)";
auto constexpr const edge_list_str =                 R"(test)";
auto constexpr const pos_pair_str =                  R"(test)";
auto constexpr const neg_pair_str =                  R"(test)";
auto constexpr const lbl_type_str =                  R"(test)";
auto constexpr const lbl_def_str =                   R"(test)";
auto constexpr const port_spec_str =                 R"(test)";
auto constexpr const port_edge_str =                 R"(test)";
auto constexpr const edge_identifier_str =           R"(test)";
auto constexpr const port_instance_str =             R"(test)";
auto constexpr const port_str =                      R"(test)";
auto constexpr const scalar_port_str =               R"(test)";
auto constexpr const bus_port_str =                  R"(test)";
auto constexpr const net_spec_str =                  R"(test)";
auto constexpr const net_instance_str =              R"(test)";
auto constexpr const net_str =                       R"(test)";
auto constexpr const scalar_net_str =                R"(test)";
auto constexpr const bus_net_str =                   R"(test)";



}
}
}

#endif //LIBSDF_TEST_SDF_TIMING_H