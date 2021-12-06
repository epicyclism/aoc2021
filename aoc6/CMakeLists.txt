cmake_minimum_required (VERSION 3.18)

add_executable(aoc6 aoc6.cpp)
add_executable(aoc6c aoc6_c.cpp)

target_link_libraries(aoc6 PRIVATE ctre::ctre)