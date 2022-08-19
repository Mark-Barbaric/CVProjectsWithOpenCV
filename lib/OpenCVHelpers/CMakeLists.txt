cmake_minimum_required(VERSION 3.19)
PROJECT(OpenCVHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCES MultipleImageWindow.cpp MultipleImageWindow.h GeneralHelpers.h)
add_library(OpenCVHelpers STATIC ${SOURCES})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

target_link_libraries(OpenCVHelpers
        CONAN_PKG::opencv)
