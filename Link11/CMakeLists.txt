cmake_minimum_required(VERSION 3.5)
project(Link11System)

set(CMAKE_CXX_STANDARD 11)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(. LINK11_SRCS)
add_library(${PROJECT_NAME} ${LINK11_SRCS})
