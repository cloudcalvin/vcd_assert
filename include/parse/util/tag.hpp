#ifndef LIBPARSE_UTIL_TAG_HPP
#define LIBPARSE_UTIL_TAG_HPP

namespace Parse::Util {

/// Create a tag from an existing type
/// \tparam Type The tag of the existing type
template <typename Type>
struct Tag {};

} // namespace Parse::Internal

#endif // LIBPARSE_UTIL_TAG_HPP
