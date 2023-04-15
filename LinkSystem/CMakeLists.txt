cmake_minimum_required(VERSION 3.5)
project(LinkSystem)

set(CMAKE_CXX_STANDARD 11)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory (Link11)
add_subdirectory (Link16)
add_subdirectory (Link22)

include_directories(${PROJECT_SOURCE_DIR}/Link11)
include_directories(${PROJECT_SOURCE_DIR}/Link16)
include_directories(${PROJECT_SOURCE_DIR}/Link22)

add_executable(${PROJECT_NAME} LinkCenter.cpp LinkCenter.h LinkSystem.cpp)
target_link_libraries(LinkSystem Link11System)
target_link_libraries(LinkSystem Link16System)
target_link_libraries(LinkSystem Link22System)
add_definitions(-fpermissive)