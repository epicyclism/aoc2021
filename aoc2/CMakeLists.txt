cmake_minimum_required (VERSION 3.18)

add_executable(aoc2 aoc2.cpp)
add_executable(aoc2_m aoc2_m.cpp)
target_include_directories(aoc2 PUBLIC ../common)
target_link_libraries(aoc2 PRIVATE ctre::ctre)