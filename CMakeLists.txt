cmake_minimum_required (VERSION 3.18)
include(FetchContent)
project ("acs_dcs")

set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare( ctre 
    GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions
    GIT_TAG origin/main
    )
FetchContent_MakeAvailable(ctre)
find_package(Boost 1.77 REQUIRED)

add_subdirectory(aoc0)
add_subdirectory(aoc1)
add_subdirectory(aoc2)
add_subdirectory(aoc3)
add_subdirectory(aoc4)
add_subdirectory(aoc5)