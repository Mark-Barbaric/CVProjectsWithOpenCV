cmake_minimum_required(VERSION 3.19)
project(Chapter5)

include(${CMAKE_SOURCE_DIR}/Cmake/conanbuildinfo.cmake)

add_executable(Chapter5 main.cpp)
set(CMAKE_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}/lib")

target_link_libraries(Chapter5 PUBLIC
        ${CONAN_LIBS}
        ObjectDetection
        )
