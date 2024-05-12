cmake_minimum_required(VERSION 3.10)
project(240510_robot)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# disable compiler specific C++ extensions like -std=gnu++11
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(240510_robot app)
