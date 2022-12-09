cmake_minimum_required(VERSION 3.19)
PROJECT(OpenCVHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCES MultipleImageWindow.cpp)
add_library(OpenCVHelpers STATIC ${SOURCES})

target_include_directories(
        OpenCVHelpers
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:/>
)

target_link_libraries(OpenCVHelpers
        CONAN_PKG::opencv)
