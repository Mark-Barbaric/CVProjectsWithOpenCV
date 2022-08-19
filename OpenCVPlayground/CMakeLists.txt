cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(OpenCVPlayground)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(SOURCES main.cpp Objects/Ball.h Objects/Color.h)
add_executable(OpenCVPlayground ${SOURCES})

target_include_directories(OpenCVPlayground PUBLIC ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(OpenCVPlayground
        CONAN_PKG::opencv)
