cmake_minimum_required(VERSION 3.19)
project(OpenCVPractice)

set(CMAKE_MACOSX_RPATH OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(BEFORE ${PROJECT_SOURCE_DIR})
set(CMAKE_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}/lib")

include(${CMAKE_SOURCE_DIR}/Cmake/conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(Chapter5)
add_subdirectory(ObjectDetection)
add_subdirectory(OpenCVHelpers)