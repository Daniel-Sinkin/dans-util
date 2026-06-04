// src/random.cpp
// https://github.com/Daniel-Sinkin/dans-util v0.2
//
#include <dans/random.hpp>
// Externals
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <random>
//

namespace dans::random
{
[[nodiscard]] def rng() -> std::mt19937_64&
{
    thread_local std::mt19937_64 engine{std::random_device{}()};
    return engine;
}

def seed(u64 value) -> void
{
    rng().seed(value);
}
}  // namespace dans::random
