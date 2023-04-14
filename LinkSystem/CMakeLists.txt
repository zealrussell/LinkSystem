cmake_minimum_required(VERSION 3.23)
project(LinkSystem)

set(CMAKE_CXX_STANDARD 11)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory (link11)
add_subdirectory (link16)
add_subdirectory (link22)


add_executable(${PROJECT_NAME} LinkCenter.cpp LinkCenter.h LinkSystem.cpp)
target_link_libraries(LinkSystem Link11System Link16System Link22System)
add_definitions(-fpermissive)