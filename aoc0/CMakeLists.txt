cmake_minimum_required (VERSION 3.18)

add_executable(aoc0 aoc0.cpp)
target_include_directories(aoc0 PUBLIC ../common)
target_link_libraries(aoc0 PRIVATE ctre::ctre)