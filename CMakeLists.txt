cmake_minimum_required(VERSION 3.10)
project(240510_robot)

list(APPEND CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/cmake
)
include(main)
set(SCRIPTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# disable compiler specific C++ extensions like -std=gnu++11
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)


ADD_SUBPROJECT(240510_robot app)


