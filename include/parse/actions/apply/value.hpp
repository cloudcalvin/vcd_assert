#ifndef LIBPARSE_ACTIONS_APPLY_VALUE_HPP
#define LIBPARSE_ACTIONS_APPLY_VALUE_HPP

namespace Parse::Apply {

template <auto Value>
struct value {
  template <class Rule, class... Stack, class State>
  static bool apply0(State &state, const Stack &... /*unused*/) {
    state = Value;
    return true;
  }
};

} // namespace Parse::Apply

#endif // LIBPARSE_ACTIONS_APPLY_VALUE_HPP
