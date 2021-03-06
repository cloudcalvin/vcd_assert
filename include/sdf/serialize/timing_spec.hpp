#ifndef LIBSDF_SERIALIZE_TIMINGSPEC_HPP
#define LIBSDF_SERIALIZE_TIMINGSPEC_HPP

#include <sdf/types/timing_spec.hpp>

#include <sdf/serialize/base.hpp>
#include <sdf/serialize/timing_check.hpp>

#include <range/v3/algorithm/copy.hpp>
#include <string_view>

namespace SDF {


/// Serialize SDF timing spec
/// \tparam OutputIterator must meet the requirements of OutputIterator
/// \param oi The OutputIterator being written to
/// \param ts The SDF file timing specification to write
/// \exception Throws if writing to the OutputIterator throws otherwise noexcept
template <class OutputIterator>
void serialize_timing_spec(OutputIterator oi, int indent,
                     TimingSpec ts) noexcept(noexcept(*oi++ = '!')) {
  //only timing checks supported at the moment.
  assert(ts.get_enum_type() == TimingSpecType::timing_check);
  serialize_indent(oi, indent);

  switch (ts.get_enum_type()) {
    case TimingSpecType::delay:
      throw std::runtime_error("InternalError : Delays Unimplemented");  
      ranges::copy(std::string_view("(DELAY \n"), oi);
      // serialize_delay_spec(oi, indent + 1, ts);
      break;
    case TimingSpecType::timing_check:
      ranges::copy(std::string_view("(TIMINGCHECK \n"), oi);
      serialize_timing_check_spec(oi, indent + 1, std::get<TimingCheckSpec>(ts.value));
      break;
    case TimingSpecType::timing_env:
      throw std::runtime_error("InternalError : TimingEnvs Unimplemented");  
      ranges::copy(std::string_view("(TIMINGENV \n"), oi);
      // serialize_timing_env_spec(oi, indent + 1, ts);
      break;
    case TimingSpecType::label:
      throw std::runtime_error("InternalError : Labels Unimplemented");  
      ranges::copy(std::string_view("(LABEL \n"), oi);
      // serialize_timing_label_spec(oi, indent + 1, ts);
      break;
    default:
      throw std::runtime_error("InternalError");
    }

  serialize_indent(oi, indent);
  ranges::copy(std::string_view(")\n"), oi);

}

} // namespace SDF

#endif // LIBSDF_SERIALIZE_TIMINGSPEC_HPP

