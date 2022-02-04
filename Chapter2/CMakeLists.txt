cmake_minimum_required(VERSION 3.16)
PROJECT(OpenCVCMake)

MESSAGE("Cmake Prefix Path: ${CMAKE_PREFIX_PATH}")
FIND_PACKAGE(OpenCV REQUIRED)
MESSAGE("OpenCV : version: ${OpenCV_Version}")


ADD_EXECUTABLE(OpenCVCMake main.cpp)
TARGET_LINK_LIBRARIES(OpenCVCMake ${OpenCV_LIBS})