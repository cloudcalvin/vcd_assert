#ifndef LIBVCD_GRAMMAR_ENUMS_VALUE_HPP
#define LIBVCD_GRAMMAR_ENUMS_VALUE_HPP

#include "../../types/enums.hpp"

#include <parse/grammar/base.h>

namespace VCD::Grammar {

using namespace Parse::Grammar::Base;

// clang-format off

/// Values
struct value_0 : one<'0'> {
  static constexpr auto value = Value::zero;
};

struct value_1 : one<'1'> {
  static constexpr auto value = Value::one;
};

struct value_x : one<'x','X'> {
  static constexpr auto value = Value::x;
};

struct value_z : one<'z','Z','?'> {
  static constexpr auto value = Value::z;
};

struct value : sor<value_1, value_0, value_x, value_z> {
  static constexpr auto error() { return "Expected value"; }
};

// clang-format on

} // namespace VCD::Grammar

#endif // LIBVCD_GRAMMAR_ENUMS_VALUE_HPP
