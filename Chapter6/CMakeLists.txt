cmake_minimum_required(VERSION 3.19)
project(Chapter6)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(Chapter6 main.cpp)

target_link_libraries(Chapter6 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )