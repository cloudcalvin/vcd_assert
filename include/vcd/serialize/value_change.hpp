#ifndef LIBVCD_SERIALIZE_VALUE_CHANGE_HPP
#define LIBVCD_SERIALIZE_VALUE_CHANGE_HPP

#include "./enums.hpp"
#include "../types/value_change.hpp"

#include <range/v3/algorithm/copy.hpp>
#include <string_view>

namespace VCD {

/// Serialize VCD scalar value change
/// \tparam OutputIterator must meet the requirements of OutputIterator
/// \param oi The OutputIterator being written to
/// \param svcv The scalar value change to write
/// \exception Throws if writing to the OutputIterator throws otherwise noexcept
template <class OutputIterator>
void serialize_value_change(
    OutputIterator oi,
    ScalarValueChangeView svcv) noexcept(noexcept(*oi++ = '!')) {
  using std::literals::string_view_literals::operator""sv;

  *oi++ = value_to_char(svcv.value);
  ranges::copy(svcv.identifier_code, oi);
  ranges::copy("\n"sv, oi);
}

/// Serialize VCD vector value change
/// \tparam OutputIterator must meet the requirements of OutputIterator
/// \param oi The OutputIterator being written to
/// \param vvcv The vector value change to write
/// \exception Throws if writing to the OutputIterator throws otherwise noexcept
template <class OutputItertator>
void serialize_value_change(OutputItertator oi,
                            VectorValueChangeView vvcv) noexcept(noexcept(*oi++ = '!')) {
  using std::literals::string_view_literals::operator""sv;

  ranges::copy("b"sv, oi);
  for (auto value : vvcv.values)
    *oi++ = value_to_char(value);
  ranges::copy(" "sv, oi);
  ranges::copy(vvcv.identifier_code, oi);
  ranges::copy("\n"sv, oi);
}

/// Serialize VCD real value change
/// \tparam OutputIterator must meet the requirements of OutputIterator
/// \param oi The OutputIterator being written to
/// \param rvcv The vector value change to write
/// \exception Throws if writing to the OutputIterator throws otherwise noexcept
template <class OutputIterator>
void serialize_value_change(OutputIterator oi,
                            RealValueChangeView rvcv) noexcept(noexcept(*oi++ = '!')) {
  using std::literals::string_view_literals::operator""sv;

  ranges::copy("r"sv, oi);
  ranges::copy(std::to_string(rvcv.value), oi);
  ranges::copy(" "sv, oi);
  ranges::copy(rvcv.identifier_code, oi);
  ranges::copy("\n"sv, oi);
}

} // namespace VCD

#endif // LIBVCD_SERIALIZE_VALUE_CHANGE_HPP
