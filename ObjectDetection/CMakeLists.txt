cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)

set(SOURCE Preprocessing.h Preprocessing.cpp)
add_library(ObjectDetection SHARED ${SOURCE})

include(${CMAKE_SOURCE_DIR}/Cmake/conanbuildinfo.cmake)

target_link_libraries(ObjectDetection
        ${CONAN_LIBS})
