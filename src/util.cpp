// src/util.cpp
// https://github.com/Daniel-Sinkin/dans-util v0.2
//
#include <dans/util.hpp>
//
// External
#include <dans/types.hpp>

namespace dans::util
{
static_assert(sizeof(usize) >= sizeof(void*));
}  // namespace dans::util
