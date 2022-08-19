cmake_minimum_required(VERSION 3.19)
project(Chapter5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(Chapter5 main.cpp)

target_include_directories(Chapter5 PUBLIC
        "${CMAKE_BINARY_DIR}/lib")

target_link_libraries(Chapter5 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )
