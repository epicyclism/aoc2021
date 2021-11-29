# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.19.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(ctre-populate NONE)

include(ExternalProject)
ExternalProject_Add(ctre-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/hanickadot/compile-time-regular-expressions" "GIT_TAG" "origin/main"
                    SOURCE_DIR          "/home/paul/src/aoc2021/build/_deps/ctre-src"
                    BINARY_DIR          "/home/paul/src/aoc2021/build/_deps/ctre-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


