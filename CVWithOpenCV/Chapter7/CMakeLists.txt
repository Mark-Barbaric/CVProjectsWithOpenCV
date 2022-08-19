cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(Chapter7)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(SOURCES main.cpp)
add_executable(Chapter7 ${SOURCES})
target_link_libraries(Chapter7
        CONAN_PKG::opencv)