cmake_minimum_required (VERSION 3.18)

add_executable(aoc13_v1 aoc13_v1.cpp)
add_executable(aoc13 aoc13.cpp)

target_link_libraries(aoc13_v1 PRIVATE ctre::ctre)
target_link_libraries(aoc13 PRIVATE ctre::ctre)