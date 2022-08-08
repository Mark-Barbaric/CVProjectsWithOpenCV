cmake_minimum_required(VERSION 3.19)
project(Chapter5)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(Chapter5 main.cpp)

target_link_libraries(Chapter5 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )

target_include_directories(Chapter5 PUBLIC
        "${CMAKE_BINARY_DIR}/lib")