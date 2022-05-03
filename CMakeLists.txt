cmake_minimum_required(VERSION 3.19)
project(OpenCVPractice)

set(CMAKE_MACOSX_RPATH OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(BEFORE ${PROJECT_SOURCE_DIR})

#==================================================================================================
#Conan

## Install and Run Conan
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

find_program(CONAN_CMD conan)

if(NOT CONAN_CMD AND CONAN_REQUIRED)
    message(FATAL_ERROR "Conan executable not found!")
endif()

set(CONAN_DISABLE_CHECK_COMPILER True)

set(conan_file "${CMAKE_SOURCE_DIR}/conanfile.py")
set(conan_install_optss "-g cmake --build=missing")

message("CMake Host System Name ${CMAKE_HOST_SYSTEM_NAME}")

set(conan_profile_file "${CMAKE_SOURCE_DIR}/conan_profiles/${CMAKE_HOST_SYSTEM_NAME}.profile")

message("Conan Profile: ${conan_profile_file}")

message(STATUS "conan install ${conan_file} -pr ${conan_profile_file} ${conan_install_optss}")
execute_process(
        COMMAND conan install "${conan_file}"
        -pr ${conan_profile_file}
        ${conan_install_opts}
        OUTPUT_FILE conan_install_output.txt
        ERROR_VARIABLE conan_install_error
        RESULT_VARIABLE conan_result)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(Chapter5)
add_subdirectory(ObjectDetection)
add_subdirectory(OpenCVHelpers)