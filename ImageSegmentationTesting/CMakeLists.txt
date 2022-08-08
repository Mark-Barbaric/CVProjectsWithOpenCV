cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(ImageSegmentationTesting)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(ImageSegmentationTesting
        ImageSegmentationTesting.cpp)

target_link_libraries(ImageSegmentationTesting
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers)

target_include_directories(ImageSegmentationTesting PUBLIC
        "${CMAKE_BINARY_DIR}/lib")

