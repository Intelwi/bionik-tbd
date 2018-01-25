cmake_minimum_required(VERSION 3.9)
project(bionik_tbd)

set(CMAKE_CXX_STANDARD 17)

add_executable(pc src/pc/main.cpp)

add_executable(robot src/robot/main.cpp)
