cmake_minimum_required(VERSION 3.20)

if(APPLE AND NOT DEFINED CMAKE_C_COMPILER AND NOT DEFINED CMAKE_CXX_COMPILER)
    foreach(DANS_TEMPLATE_LLVM_PREFIX IN ITEMS /opt/homebrew/opt/llvm /usr/local/opt/llvm)
        if(EXISTS "${DANS_TEMPLATE_LLVM_PREFIX}/bin/clang" AND EXISTS "${DANS_TEMPLATE_LLVM_PREFIX}/bin/clang++")
            set(CMAKE_C_COMPILER "${DANS_TEMPLATE_LLVM_PREFIX}/bin/clang" CACHE FILEPATH "C compiler" FORCE)
            set(CMAKE_CXX_COMPILER "${DANS_TEMPLATE_LLVM_PREFIX}/bin/clang++" CACHE FILEPATH "C++ compiler" FORCE)
            message(STATUS "Using LLVM toolchain from ${DANS_TEMPLATE_LLVM_PREFIX}")
            break()
        endif()
    endforeach()
endif()

project(dans_template LANGUAGES C CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DANS_CORE_SOURCE_DIR "" CACHE PATH "Optional local checkout of dans-core")
if(DANS_CORE_SOURCE_DIR)
    add_subdirectory("${DANS_CORE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/_deps/dans-core-build")
else()
    include(FetchContent)
    FetchContent_Declare(
        dans_core
        GIT_REPOSITORY git@github.com:Daniel-Sinkin/dans-core.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(dans_core)
endif()

add_library(dans_template_warnings INTERFACE)
target_compile_options(dans_template_warnings INTERFACE
    $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wconversion
        -Wfloat-conversion
        -Wsign-conversion
        -Wcast-qual
        -Wcast-align
        -Wformat=2
        -Wundef
        -Wnull-dereference
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wold-style-cast
        -Wzero-as-null-pointer-constant
        -Wdouble-promotion
        -Wimplicit-fallthrough
        -Wreturn-type>
    $<$<CXX_COMPILER_ID:Clang,AppleClang>:
        -Wconditional-uninitialized
        -Wextra-semi
        -Wimplicit-int-conversion
        -Wimplicit-int-float-conversion
        -Wnewline-eof
        -Wshorten-64-to-32
        -Wswitch-enum
        -Wunreachable-code>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches
        -Wduplicated-cond
        -Wlogical-op
        -Wsign-compare
        -Wuseless-cast>
)

add_executable(dans_template
    app/main.cpp
)
target_link_libraries(dans_template PRIVATE
    dans::core
    dans_template_warnings
)
target_precompile_headers(dans_template PRIVATE
    <dans/pch.hpp>
)
