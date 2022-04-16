cmake_minimum_required(VERSION 3.19)
project(Chapter5)

find_package(OPENCV)

add_executable(OpenCVPractice main.cpp)
target_link_libraries(OpenCVPractice OPENCV)