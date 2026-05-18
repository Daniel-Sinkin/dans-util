// app/main.cpp

#include <dans/development_markers.hpp>
#include <dans/types.hpp>

#include <chrono>
#include <format>
#include <print>
#include <string>
#include <string_view>

namespace dans_template
{
namespace
{
def append_time_unit(
    mut std::string& result,
    mut bool& started,
    std::chrono::milliseconds::rep value,
    std::string_view singular,
    std::string_view plural
) -> void
{
    if (not started and value == 0)
    {
        return;
    }
    if (not result.empty())
    {
        result += ' ';
    }
    result += std::format("{} {}", value, value == 1 ? singular : plural);
    started = true;
}
}  // namespace

def format_seconds(std::chrono::duration<dans::f64> dur, bool show_milliseconds = false)
    -> std::string
{
    const auto is_negative = dur < std::chrono::duration<dans::f64>::zero();
    const auto positive_duration = is_negative ? -dur : dur;

    constexpr std::chrono::milliseconds::rep ms_per_second = 1000;
    constexpr std::chrono::milliseconds::rep ms_per_minute = ms_per_second * 60;
    constexpr std::chrono::milliseconds::rep ms_per_hour = ms_per_minute * 60;
    constexpr std::chrono::milliseconds::rep ms_per_day = ms_per_hour * 24;

    mut auto remaining =
        std::chrono::duration_cast<std::chrono::milliseconds>(positive_duration).count();

    const auto days = remaining / ms_per_day;
    remaining %= ms_per_day;
    const auto hours = remaining / ms_per_hour;
    remaining %= ms_per_hour;
    const auto minutes = remaining / ms_per_minute;
    remaining %= ms_per_minute;
    const auto seconds = remaining / ms_per_second;
    const auto milliseconds = remaining % ms_per_second;

    mut std::string result{};
    mut bool started = false;

    append_time_unit(result, started, days, "day", "days");
    append_time_unit(result, started, hours, "hour", "hours");
    append_time_unit(result, started, minutes, "minute", "minutes");
    append_time_unit(result, started, seconds, "second", "seconds");
    if (show_milliseconds)
    {
        append_time_unit(result, started, milliseconds, "millisecond", "milliseconds");
    }

    if (not started)
    {
        result = show_milliseconds ? "0 milliseconds" : "0 seconds";
    }

    if (is_negative)
    {
        return std::format("-{}", result);
    }
    return result;
}
}  // namespace dans_template

def main() -> int
{
    std::println(
        "Hello, Template! Don't forget to adjust the project name in the CMakeLists.txt "
        "and the namespace in src/*.cpp files"
    );
}
