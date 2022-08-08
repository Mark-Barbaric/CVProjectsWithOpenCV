cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)

set(SOURCE Preprocessing.h Preprocessing.cpp Segmentation.cpp Segmentation.h)
add_library(ObjectDetection STATIC ${SOURCE})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

target_link_libraries(ObjectDetection
        OpenCVHelpers
        CONAN_PKG::opencv)
