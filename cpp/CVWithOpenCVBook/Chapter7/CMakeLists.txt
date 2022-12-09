cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(Chapter7)

add_definitions(-DRESOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/Resources)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCES main.cpp)
add_executable(Chapter7 ${SOURCES})
target_link_libraries(Chapter7
        CONAN_PKG::opencv)

        