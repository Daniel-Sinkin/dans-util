// app/main.cpp

#include <dans/development_markers.hpp>
#include <dans/types.hpp>

#include <print>

namespace dans_template
{

}  // namespace dans_template

def main() -> int
{
    std::println(
        "Hello, Template! Don't forget to adjust the project name in the CMakeLists.txt "
        "and the namespace in src/*.cpp files"
    );
}
