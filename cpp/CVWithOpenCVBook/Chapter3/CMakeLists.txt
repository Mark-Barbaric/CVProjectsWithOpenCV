cmake_minimum_required(VERSION 3.16)
project(Contours)
set(CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(Contours Contours.cpp)
target_link_libraries(Contours ${OpenCV_LIBS})