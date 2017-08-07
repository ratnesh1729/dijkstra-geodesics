cmake_minimum_required(VERSION 2.8)
include_directories(".")
PROJECT(fit)
SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(dijkstra)
