// include/dans/math.hpp
// Externals
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <cassert>
#include <concepts>
#include <numbers>
#include <utility>
//

#pragma once
#ifndef DANS_MATH_HPP
#define DANS_MATH_HPP

namespace dans::math
{
inline constexpr auto pi = std::numbers::pi;
inline constexpr auto two_pi = 2.0 * pi;
inline constexpr auto tau = two_pi;
inline constexpr auto half_pi = pi / 2.0;
inline constexpr auto quarter_pi = pi / 4.0;
inline constexpr auto inv_pi = std::numbers::inv_pi;
inline constexpr auto e = std::numbers::e;
inline constexpr auto sqrt2 = std::numbers::sqrt2;
inline constexpr auto sqrt3 = std::numbers::sqrt3;
inline constexpr auto inv_sqrt3 = std::numbers::inv_sqrt3;
inline constexpr auto inv_sqrtpi = std::numbers::inv_sqrtpi;
inline constexpr auto ln2 = std::numbers::ln2;
inline constexpr auto ln10 = std::numbers::ln10;

template <typename T, typename U, typename V>
    requires requires(T x, U lo, V hi) {
        std::cmp_less_equal(lo, x);
        std::cmp_less_equal(x, hi);
        std::cmp_less_equal(lo, hi);
    }
[[nodiscard]] constexpr def in_interval(T x, U lo, V hi) -> bool
{
    assert(std::cmp_less_equal(lo, hi));
    return std::cmp_less_equal(lo, x) and std::cmp_less_equal(x, hi);
}

template <std::floating_point T>
[[nodiscard]] constexpr def in_interval(T x, T lo, T hi) -> bool
{
    assert(lo <= hi);
    return lo <= x and x <= hi;
}
}  // namespace dans::math

#endif  // DANS_MATH_HPP
