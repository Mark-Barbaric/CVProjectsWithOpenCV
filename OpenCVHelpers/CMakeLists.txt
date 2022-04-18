cmake_minimum_required(VERSION 3.19)
PROJECT(OpenCVHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCES MultipleImageWindow.cpp MultipleImageWindow.h)
add_library(OpenCVHelpers SHARED ${SOURCES})

include(${CMAKE_SOURCE_DIR}/Cmake/conanbuildinfo.cmake)

target_link_libraries(ObjectDetection
        ${CONAN_LIBS})
