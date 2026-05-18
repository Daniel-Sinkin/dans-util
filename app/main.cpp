// app/main.cpp
// Externals
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <array>
#include <chrono>
#include <format>
#include <print>
#include <string>
#include <string_view>
#include <vector>
//

namespace dans
{
[[nodiscard]] def format_seconds(std::chrono::duration<f64> dur, bool show_milliseconds = false)
    -> std::string
{
    const auto is_negative = dur < std::chrono::duration<f64>::zero();
    const auto positive_duration = is_negative ? -dur : dur;

    using Msec = std::chrono::milliseconds;
    constexpr Msec::rep ms_per_second{1000};
    constexpr Msec::rep ms_per_minute{ms_per_second * 60};
    constexpr Msec::rep ms_per_hour{ms_per_minute * 60};
    constexpr Msec::rep ms_per_day{ms_per_hour * 24};

    mut auto remaining = std::chrono::duration_cast<Msec>(positive_duration).count();

    const auto days = remaining / ms_per_day;
    remaining %= ms_per_day;
    const auto hours = remaining / ms_per_hour;
    remaining %= ms_per_hour;
    const auto minutes = remaining / ms_per_minute;
    remaining %= ms_per_minute;
    const auto seconds = remaining / ms_per_second;
    const auto milliseconds = remaining % ms_per_second;

    mut std::string result{};
    mut auto started = false;

    const auto append_time_unit = [&](Msec::rep value, std::string_view name) -> void
    {
        if (not started and value == 0) return;
        if (not result.empty()) result += ' ';
        result += std::format("{} {}{}", value, name, value == 1 ? "" : "s");
        started = true;
    };
    append_time_unit(days, "day");
    append_time_unit(hours, "hour");
    append_time_unit(minutes, "minute");
    append_time_unit(seconds, "second");
    if (show_milliseconds) append_time_unit(milliseconds, "millisecond");

    if (not started) result = show_milliseconds ? "0 milliseconds" : "0 seconds";

    if (is_negative) return std::format("-{}", result);
    return result;
}

class ScopeTimer
{
    using Clock = std::chrono::steady_clock;

  public:
    ScopeTimer(std::string_view name, bool print_millis = false)
        : name_{name}, start_{Clock::now()}, print_millis_{print_millis}
    {
    }
    ~ScopeTimer()
    {
        try
        {
            const std::chrono::duration<f64> dur{Clock::now() - start_};
            std::println("{} finished in {}.", name_, format_seconds(dur, print_millis_));
        }
        catch (...)
        {
        }
    }

  private:
    std::string_view name_{};
    std::chrono::time_point<Clock> start_{};
    bool print_millis_{false};
};

[[nodiscard]] def split(std::string_view text, char delim) -> std::vector<std::string_view>
{
    mut std::vector<std::string_view> out{};
    mut auto left = 0zu;
    while (true)
    {
        const auto pos = text.find(delim, left);
        if (pos == std::string_view::npos) break;
        out.push_back(text.substr(left, pos - left));
        left = pos + 1;
    }
    out.push_back(text.substr(left));
    return out;
}

namespace
{
[[nodiscard]] def format_bytes_with(
    u64 bytes, f64 divisor, const std::array<std::string_view, 7>& suffixes) -> std::string
{
    mut auto value = static_cast<f64>(bytes);
    mut auto index = 0zu;
    while (value >= divisor and index + 1 < suffixes.size())
    {
        value /= divisor;
        ++index;
    }
    if (index == 0) return std::format("{} {}", bytes, suffixes[0]);

    mut auto formatted = std::format("{:.2f}", value);
    while (formatted.back() == '0') formatted.pop_back();
    if (formatted.back() == '.') formatted.pop_back();
    return std::format("{} {}", formatted, suffixes[index]);
}
}  // namespace

[[nodiscard]] def format_bytes_binary(u64 bytes) -> std::string
{
    constexpr std::array<std::string_view, 7> suffixes{
        "B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
    return format_bytes_with(bytes, 1024.0, suffixes);
}

[[nodiscard]] def format_bytes_decimal(u64 bytes) -> std::string
{
    constexpr std::array<std::string_view, 7> suffixes{
        "B", "KB", "MB", "GB", "TB", "PB", "EB"};
    return format_bytes_with(bytes, 1000.0, suffixes);
}
}  // namespace dans

def main() -> int
{
    using namespace dans;
    using Duration = std::chrono::duration<f64>;
    std::println("{}", format_seconds(Duration{123 * 86400.0 + 13 * 3600 + 22 * 60 + 12}));
    std::println("{}", format_seconds(Duration{5 * 3600.0 + 30}, true));
    std::println("{}", format_seconds(Duration{0}, true));
}
