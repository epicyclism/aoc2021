# aoc2021
Advent Of Code 2021

aoc0 is a placeholder, currently a solution to Day 16 from 2018 IIRC.

Each new day of 2021 will get it's own directory, at least that's the plan. Builds should be good on MacOS, Windows and Linux. Using Monterey, 10 and Ubuntu 20.04 but with gcc 11.

In case I forget...

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/home/paul/vcpkg/scripts/buildsystems/vcpkg.cmake

(Path according to situation)

VSCode and Visual Studio ought to take care of this though.
