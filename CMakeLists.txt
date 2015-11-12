cmake_minimum_required(VERSION 3.3)
project(homework_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Bloom.cpp Bloom.h)
add_executable(homework_3 ${SOURCE_FILES})