cmake_minimum_required (VERSION 3.18)

add_executable(aoc12 aoc12.cpp)
add_executable(aoc12_o aoc12_o.cpp)
target_include_directories(aoc12_o PUBLIC ../common)
target_link_libraries(aoc12_o PRIVATE ctre::ctre)