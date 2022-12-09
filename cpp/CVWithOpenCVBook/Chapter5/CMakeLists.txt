cmake_minimum_required(VERSION 3.19)
project(Chapter5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(
        ${CMAKE_SOURCE_DIR}/lib
)

add_executable(Chapter5 main.cpp)

target_link_libraries(Chapter5 PUBLIC
        CONAN_PKG::opencv
        ObjectDetection
        OpenCVHelpers
        )
