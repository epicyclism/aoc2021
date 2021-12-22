cmake_minimum_required (VERSION 3.18)

add_executable(aoc23 aoc23.cpp)
target_include_directories(aoc23 PUBLIC ../common)
target_link_libraries(aoc22 PRIVATE ctre::ctre)