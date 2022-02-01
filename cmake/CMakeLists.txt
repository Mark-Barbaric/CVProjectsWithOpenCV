cmake_minimum_required(VERSION 3.18)
project(CMakeTest)
set (CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
FIND_PACKAGE(OpenCV REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")
include_directories( ${OpenCV_INCLUDE_DIRS} )


