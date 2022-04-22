cmake_minimum_required(VERSION 3.19)
PROJECT(OpenCVHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCES MultipleImageWindow.cpp MultipleImageWindow.h)
add_library(OpenCVHelpers SHARED ${SOURCES})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

target_link_libraries(OpenCVHelpers
        ${CONAN_LIBS})
