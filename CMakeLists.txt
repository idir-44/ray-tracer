cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(raytracer VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(raytracer main.cpp)
