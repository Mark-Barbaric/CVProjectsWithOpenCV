cmake_minimum_required(VERSION 3.19)
PROJECT(OpenCVHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCES MultipleImageWindow.cpp MultipleImageWindow.h GeneralHelpers.h)
add_library(OpenCVHelpers SHARED ${SOURCES})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

target_link_libraries(OpenCVHelpers
        CONAN_PKG::opencv)

set_target_properties(OpenCVHelpers PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib"
        )