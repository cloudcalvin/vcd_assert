#ifndef LIBVCD_TYPES_SCOPE_HPP
#define LIBVCD_TYPES_SCOPE_HPP

#include "./enums.hpp"

#include <unordered_map>
#include <string>

namespace VCD {

/// View of scope data
/// \todo Ensure identifier correctness
struct ScopeDataView {
  ScopeType type;
  std::string_view identifier;
};

/// VCD Scope object
/// This object is defined in terms of the Header it is contained in and can
/// therefore only be populated alongside the Header with HeaderReader
/// \related HeaderReader
class Scope {
  ScopeType type_;         /// The scope type
  std::string identifier_; /// The scope identifier

  /// Child scopes
  std::unordered_map<std::string, std::size_t> child_scopes_;

  /// Child variables
  std::unordered_map<std::string, std::size_t> child_variables_;

  friend class HeaderReader;
public:
  /// The scope constructor
  /// \todo Ensure identifier correctness
  /// \param type The scope type
  /// \param identifier The identifier string
  /// \todo ensure identifier correctness
  Scope(ScopeType type, std::string identifier) noexcept;

  /// True if the scope directly contains the variable reference
  /// \param reference The variable reference
  /// \returns Wether the scope directly contains the variable reference
  bool contains_variable(std::string &reference) const noexcept;

  /// Get the variable index by reference
  /// \param reference The variable reference
  /// \returns The variable index
  std::size_t get_variable_index(std::string &reference) const;

  /// Number of variables directly in this scope
  /// \returns The number of variables directly in this scope
  std::size_t num_variables() const noexcept;

  /// True if the scope directly contains the scope
  /// \param identifier The child scope identifier
  /// \returns Wether the scope directly contains \p identifier
  bool contains_scope(std::string &identifier) const noexcept;

  /// Get scope index by identifierthis
  /// \param identifier The child scope identifier
  /// \returns The scope index from \p identifier
  std::size_t get_scope_index(std::string &identifier) const;

  /// Returns the number of direct scopes within this scope
  /// \returns The number of direct scopes within this scope
  std::size_t num_scopes() const noexcept;

  /// Get scope identifier
  /// \returns View of identifier string
  std::string_view get_identifier() const noexcept;

  /// Get scope type
  /// \returns The scope type
  ScopeType get_scope_type() const noexcept;

  /// Convert to ScopeDataView
  /// \returns ScopeDataView of Scope
  operator ScopeDataView() const noexcept;
};

} // VCD

#endif //LIBVCD_TYPES_SCOPE_HPP