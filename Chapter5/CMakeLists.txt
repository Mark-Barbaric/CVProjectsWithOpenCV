cmake_minimum_required(VERSION 3.19)
project(Chapter5)

find_package(OpenCV)

add_executable(Chapter5 main.cpp)
target_link_libraries(Chapter5 PUBLIC
        OPENCV
        ObjectDetection)

