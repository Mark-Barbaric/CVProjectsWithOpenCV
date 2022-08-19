cmake_minimum_required(VERSION 3.19)
project(Chapter6)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(Chapter6 main.cpp)

target_include_directories(Chapter6 PUBLIC
        "${CMAKE_BINARY_DIR}/lib")

target_link_libraries(Chapter6 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )


