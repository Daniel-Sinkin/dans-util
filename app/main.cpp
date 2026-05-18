// app/main.cpp
// Externals
#include <dans/chrono.hpp>
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <array>
#include <chrono>
#include <format>
#include <print>
#include <string>
#include <string_view>
//

namespace dans
{
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
    using Duration = std::chrono::duration<dans::f64>;
    std::println(
        "{}", dans::chrono::format_seconds(Duration{123 * 86400.0 + 13 * 3600 + 22 * 60 + 12}));
    std::println("{}", dans::chrono::format_seconds(Duration{5 * 3600.0 + 30}, true));
    std::println("{}", dans::chrono::format_seconds(Duration{0}, true));
}
