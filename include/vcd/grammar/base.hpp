#ifndef LIBVCD_GRAMMAR_BASE_HPP
#define LIBVCD_GRAMMAR_BASE_HPP

#include "parse/grammar/base.h"
#include "parse/grammar/part.h"

#include "./enums/value.hpp"
#include "./keywords.hpp"

namespace VCD::Grammar {

using namespace Parse::Grammar::Base;

struct blank : one<' ', '\n', '\r', '\t', '\v', '\f'> {};
struct plus_blank : plus<blank> {
  static constexpr auto error() { return "Expected whitespace"; }
};

struct command_separator : sor<
  eof,
  plus<blank>
> {};

struct printable_ascii_except_whitespace : range<33,126> {};

// TODO be strict about what is allowed as identifiers
struct identifier_code : seq<
  not_at<command_separator>,
  until<at<command_separator>>
> {};

struct simple_identifier : seq<
  tao::pegtl::identifier_first,
  star<sor<
    tao::pegtl::alnum,
    one<'_','$'>
  >>
> {};

struct escaped_identifier : seq<
  one<'\\'>,
  plus<printable_ascii_except_whitespace>,
  must<blank>
> {};

struct identifier : sor<
  escaped_identifier,
  simple_identifier
> {};

} // namespace VCD::Grammar

#endif // LIBVCD_GRAMMAR_BASE_HPP
