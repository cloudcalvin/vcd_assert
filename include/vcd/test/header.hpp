#ifndef LIBVCD_TEST_HEADER_HPP
#define LIBVCD_TEST_HEADER_HPP

#include "./scope.hpp"

#include "vcd/types/enums.hpp"
#include "vcd/types/header_reader.hpp"

namespace VCD::Test {

struct TestHeader {
  std::optional<VCD::TimeScale> time_scale;
  std::optional<std::string> date;
  std::optional<std::string> version;

  std::optional<TestScope> root_scope;
};

void read_in_test_header(VCD::HeaderReader &reader, TestHeader &test);

} // namespace VCD::Test

#endif // LIBVCD_TEST_HEADER_HPP
