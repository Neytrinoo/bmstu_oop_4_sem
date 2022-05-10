cmake_minimum_required(VERSION 3.17)
project(lab_02)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(CMAKE_CXX_FLAGS "-v")

add_executable(lab_02 main.cpp include/ListNode.hpp include/Exceptions.h include/ReverseIterator.h)