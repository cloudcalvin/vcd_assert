#include <sdf/actions/time_scale.hpp>
#include <parse/test/parse.hpp>

#include <catch2/catch.hpp>

using namespace SDF;

constexpr char timescale_str2[] = "(TIMESCALE 10ns)";

TEST_CASE("SDF.Actions.TimeScale", "[SDF][Actions][TimeScale]")
{
  using Parse::Test::require_parse;

  TimeScaleView event{};
  require_parse<Grammar::timescale, Actions::TimeScaleAction>(timescale_str2, event);
  
  SECTION("Timescale"){
    REQUIRE(event.unit == TimeScaleUnit::ns);
    REQUIRE(event.number == TimeScaleNumber::_10);
  }
}
