# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/paul/aoc2021

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/paul/aoc2021/build

# Utility rule file for NightlyConfigure.

# Include any custom commands dependencies for this target.
include _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/progress.make

_deps/ctre-build/CMakeFiles/NightlyConfigure:
	cd /Users/paul/aoc2021/build/_deps/ctre-build && /Applications/CMake.app/Contents/bin/ctest -D NightlyConfigure

NightlyConfigure: _deps/ctre-build/CMakeFiles/NightlyConfigure
NightlyConfigure: _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/build.make
.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
_deps/ctre-build/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure
.PHONY : _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/build

_deps/ctre-build/CMakeFiles/NightlyConfigure.dir/clean:
	cd /Users/paul/aoc2021/build/_deps/ctre-build && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/clean

_deps/ctre-build/CMakeFiles/NightlyConfigure.dir/depend:
	cd /Users/paul/aoc2021/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/paul/aoc2021 /Users/paul/aoc2021/build/_deps/ctre-src /Users/paul/aoc2021/build /Users/paul/aoc2021/build/_deps/ctre-build /Users/paul/aoc2021/build/_deps/ctre-build/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ctre-build/CMakeFiles/NightlyConfigure.dir/depend

