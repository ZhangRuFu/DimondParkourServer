cmake_minimum_required(VERSION 3.7)
project(DimondParkour)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/main.cpp source/Encoding.cpp source/SerializeStream.cpp source/Message.cpp header/Convert.h source/Convert.cpp)
add_executable(DimondParkour ${SOURCE_FILES})