#ifndef LIBSDF_ACTIONS_BASE_HPP
#define LIBSDF_ACTIONS_BASE_HPP

#include <sdf/grammar/base.hpp>
#include <sdf/types/base.hpp>

#include "parse/actions/apply/float.hpp"
#include "parse/actions/apply/integer.hpp"
#include "parse/actions/apply/rule_value.hpp"
#include "parse/actions/apply/string.hpp"
#include "parse/actions/apply/value.hpp"
#include "parse/actions/command/apply.hpp"
#include "parse/actions/command/apply0.hpp"
#include "parse/actions/command/inner_action.hpp"
#include "parse/actions/command/pegtl_action.hpp"
#include "parse/actions/dispatch.hpp"
#include "parse/actions/storage/function.hpp"
#include "parse/actions/storage/member.hpp"
#include "parse/actions/storage/push_back.hpp"

namespace SDF {
namespace Actions {

using namespace Parse;  

struct QStringAction : single_dispatch<
    Grammar::qstring_content, apply<Apply::string>
> {
  using state = std::string;
};

struct HCharAction : all_dispatch<apply0<Apply::rule_value>> {
  using state = HChar;
};

struct IdentifierAction : single_dispatch<
    Grammar::identifier, apply<Apply::string>
> {
  using state = std::string;
};

struct IdentifierArrayAction : single_dispatch<
    Grammar::identifier, inner_action<
      IdentifierAction, 
      Storage::push_back
    >
> {
  using state = std::vector<std::string>;
};

struct HierarchicalIdentifierStorage{
  static bool store(HierarchicalIdentifier &hi, std::string s) {
     hi.value.push_back(std::move(s));
     return true;
   }
 };

struct HierarchicalIdentifierAction : multi_dispatch<
    Grammar::hchar, inner_action<
      HCharAction, 
      Storage::member<&HierarchicalIdentifier::sep>
    >,
    Grammar::identifier, inner_action<
      IdentifierAction, 
      HierarchicalIdentifierStorage
    >
> {
  using state = HierarchicalIdentifier;
};



// blank
// plus_blank
// comment_single_line
// comment_multi_line_cont
// comment_multi_line
// comment
// sp
// sps
// sep_seq
// sep_must
// op_sep_seq
// op_sep_must
// open
// close
// block
// special_character_without_brackets
// special_character_without_backslash
// special_character
// decimal_digit
// alphanumeric
// sign
// hchar
// character
// escaped_character
// character
// any_character

}
}

#endif // LIBSDF_ACTIONS_BASE_HPP
