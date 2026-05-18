// include/dans/views.hpp
// Externals
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <ranges>
#include <utility>
//

#pragma once
#ifndef DANS_VIEWS_HPP
#define DANS_VIEWS_HPP

namespace dans::views
{
using std::views::zip;

template <std::ranges::viewable_range R>
[[nodiscard]] constexpr def enumerate(R&& r) -> decltype(auto)
{
    return std::views::zip(std::views::iota(usize{0}), std::forward<R>(r));
}
}  // namespace dans::views

#endif  // DANS_VIEWS_HPP
