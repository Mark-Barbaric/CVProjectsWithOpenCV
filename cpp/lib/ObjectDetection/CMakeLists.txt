cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/lib/
)

set(SOURCE Preprocessing.cpp Segmentation.cpp)
add_library(ObjectDetection STATIC ${SOURCE})

target_include_directories(
        ObjectDetection
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:/>
)

target_link_libraries(ObjectDetection
        OpenCVHelpers
        CONAN_PKG::opencv)
