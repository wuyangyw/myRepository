cmake_minimum_required(VERSION 3.0)

project(SOLDIERFIRE)

set(CMAKE_BUILD_TYPE "Debug")

include_directories(include)

add_executable(main_cmake main.cpp src/Soldier.cpp src/Gun.cpp)
