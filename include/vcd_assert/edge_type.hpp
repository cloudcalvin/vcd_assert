#ifndef VCD_ASSERT_2D_LUT_HPP
#define VCD_ASSERT_2D_LUT_HPP

#include <vcd/types/enums.hpp>
#include <string_view>

#include <cstdio>
#include <cstdlib>

namespace VCDAssert {

enum class EdgeType {
  NoEdge,
  PosEdge,
  NegEdge,
  Edge,
  _01,
  _10,
  _0z,
  _z1,
  _1z,
  _z0
};

constexpr std::string_view edge_type_to_string(EdgeType et)
{
  switch (et) {
  case EdgeType::NoEdge:
    return "NoEdge";
  case EdgeType::PosEdge:
    return "PosEdge";
  case EdgeType::NegEdge:
    return "NegEdge";
  case EdgeType::Edge:
    return "Edge";
  case EdgeType::_01:
    return "01";
  case EdgeType::_10:
    return "10";
  case EdgeType::_0z:
    return "0z";
  case EdgeType::_z1:
    return "z1";
  case EdgeType::_1z:
    return "1z";
  case EdgeType::_z0:
    return "z0";
  default:                                             // LCOV_EXCL_LINE
    std::puts("UNREACHABLE CODE: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                      // LCOV_EXCL_LINE
  }
}

EdgeType get_edge_type(VCD::Value from, VCD::Value to);
bool edge_type_matches(EdgeType type, VCD::Value from, VCD::Value to);

} // namespace VCDAssert

#endif // VCD_ASSERT_2D_LUT_HPP
