cmake_minimum_required (VERSION 3.18)

add_executable(aoc24 aoc24.cpp)
add_executable(aoc24_o aoc24_o.cpp)
target_include_directories(aoc24 PUBLIC ../common)
target_link_libraries(aoc24 PRIVATE ctre::ctre)
target_include_directories(aoc24_o PUBLIC ../common)
target_link_libraries(aoc24_o PRIVATE ctre::ctre)