cmake_minimum_required (VERSION 3.18)

add_executable(aoc14 aoc14.cpp)
target_include_directories(aoc14 PUBLIC ../common)
target_link_libraries(aoc14 PRIVATE ctre::ctre)