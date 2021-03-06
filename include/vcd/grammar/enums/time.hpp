#ifndef LIBVCD_GRAMMAR_ENUMS_TIME_HPP
#define LIBVCD_GRAMMAR_ENUMS_TIME_HPP

#include "../../types/enums.hpp"

#include <parse/grammar/base.h>

namespace VCD::Grammar {

using namespace Parse::Grammar::Base;

// clang-format off

/// Time units
struct time_s : string<'s'> {
  static constexpr auto value = TimeUnit::s;
};

struct time_ms : string<'m','s'> {
  static constexpr auto value = TimeUnit::ms;
};

struct time_us : string<'u','s'> {
  static constexpr auto value = TimeUnit::us;
};

struct time_ns : string<'n','s'> {
  static constexpr auto value = TimeUnit::ns;
};

struct time_ps : string<'p','s'> {
  static constexpr auto value = TimeUnit::ps;
};

struct time_fs : string<'f','s'> {
  static constexpr auto value = TimeUnit::fs;
};

struct time_unit : sor<time_s, time_ms, time_us, time_ns, time_ps, time_fs> {
  static constexpr auto error() { return "Expected time unit"; }
};

struct time_number : seq<
  one<'1'>,
  opt<
    one<'0'>,
    opt<
      one<'0'>
    >
  >
> {};

// clang-format on

} // namespace VCD::Grammar

#endif // LIBVCD_GRAMMAR_ENUMS_TIME_HPP
