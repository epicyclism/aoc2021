cmake_minimum_required (VERSION 3.18)

add_executable(aoc21 aoc21.cpp)
target_include_directories(aoc21 PUBLIC ../common)
target_link_libraries(aoc21 PRIVATE ctre::ctre)