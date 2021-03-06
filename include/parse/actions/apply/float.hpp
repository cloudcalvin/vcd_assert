#ifndef LIBPARSE_ACTIONS_APPLY_FLOAT_HPP
#define LIBPARSE_ACTIONS_APPLY_FLOAT_HPP

#include <string>

namespace Parse::Apply {

struct float_value {
  template <class Rule, class ActionInput, class... Stack, class State>
  static bool apply(const ActionInput &input, State &state,
                    const Stack &... /*unused*/
  ) {
    state = std::stod(input.string());
    return true;
  }
};

} // namespace Parse::Apply

#endif // LIBPARSE_ACTIONS_APPLY_FLOAT_HPP
