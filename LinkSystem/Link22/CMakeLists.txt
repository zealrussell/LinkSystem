cmake_minimum_required(VERSION 3.23)
project(Link22Ssystem)

set(CMAKE_CXX_STANDARD 11)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(${PROJECT_NAME} 
Utils/Link22Variable.h
Utils/MsgUtil.cpp Utils/MsgUtil.h 
Utils/CrcUtil.cpp Utils/CrcUtil.h 
Utils/RSInclude/gf.hpp Utils/RSInclude/rs.hpp  Utils/RSInclude/poly.hpp 
Utils/AESUtil.cpp Utils/AESUtil.h 

System/ConstructCenter.cpp System/ConstructCenter.h 
System/F0nMessage.cpp System/F0nMessage.h 
System/FnpMessage.cpp System/FnpMessage.h 
System/FnMessage.cpp System/FnMessage.h
)