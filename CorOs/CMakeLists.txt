# CMakeList.txt : CMake project for CorOs, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (CorOs "_OLD/kernel.c" "kernel.h"  "kernel.c")

# TODO: Add tests and install targets if needed.
