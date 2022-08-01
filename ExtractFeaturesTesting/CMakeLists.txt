cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(ExtractFeaturesTesting)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(ExtractFeaturesTesting
        ExtractFeatures.cpp ExtractFeatures.h
        ExtractFeaturesTesting.cpp)
target_link_libraries(ExtractFeaturesTesting
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers)

target_include_directories(ExtractFeaturesTesting PUBLIC
        "${CMAKE_BINARY_DIR}/lib")

