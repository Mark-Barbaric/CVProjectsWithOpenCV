cmake_minimum_required(VERSION 3.19)
project(Chapter5)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_executable(Chapter5 main.cpp)
set(CMAKE_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}/lib")

target_link_libraries(Chapter5 PUBLIC
        ${CONAN_LIBS}
        ObjectDetection
        )
