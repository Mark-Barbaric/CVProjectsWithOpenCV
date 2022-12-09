cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(OpenCVPlayground)

set(SOURCES main.cpp Shape.h Color.h)
add_executable(OpenCVPlayground ${SOURCES})

target_include_directories(OpenCVPlayground PUBLIC ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(OpenCVPlayground
        CONAN_PKG::opencv)

