cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)

set(SOURCE Preprocessing.h Preprocessing.cpp Segmentation.cpp Segmentation.h)
add_library(ObjectDetection SHARED ${SOURCE})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

target_link_libraries(ObjectDetection
        ${CONAN_LIBS})
