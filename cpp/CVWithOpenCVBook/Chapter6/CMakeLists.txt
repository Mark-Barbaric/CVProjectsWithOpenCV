cmake_minimum_required(VERSION 3.19)
project(Chapter6)

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(Chapter6 main.cpp)

target_link_libraries(Chapter6 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )


