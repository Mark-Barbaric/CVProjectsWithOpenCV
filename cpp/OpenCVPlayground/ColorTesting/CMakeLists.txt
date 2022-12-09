project(ColorTesting)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES main.cpp)
add_executable(ColorTesting ${SOURCES})

target_include_directories(ColorTesting PUBLIC ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(ColorTesting
        CONAN_PKG::opencv)