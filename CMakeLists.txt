cmake_minimum_required(VERSION 3.9)
project(bionik_tbd)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/lib/cmake)

find_package(Threads REQUIRED)
find_package(Boost 1.56 REQUIRED COMPONENTS system program_options)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(pc src/pc/main.cpp)

add_executable(robot src/robot/main.cpp src/robot/LineDetector.cpp src/robot/LineDetector.h src/robot/FrameJpgUdpStreamer.cpp src/robot/FrameJpgUdpStreamer.h)
target_link_libraries(robot Threads::Threads Boost::system Boost::program_options ${OpenCV_LIBS})
