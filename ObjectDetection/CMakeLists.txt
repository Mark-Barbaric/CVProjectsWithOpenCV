cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)

set(SOURCE Preprocessing.h Preprocessing.cpp Segmentation.cpp Segmentation.h)
add_library(ObjectDetection SHARED ${SOURCE})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

target_link_libraries(ObjectDetection
        OpenCVHelpers
        CONAN_PKG::opencv)

set_target_properties(Dynamo PROPERTIES FOLDER "Libraries")

set_target_properties(
        ${_target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
if(UNIX)
    set_target_properties(
            # Forsing to use still RPATH instead of RUNPATH because of
            # https://bugs.launchpad.net/ubuntu/+source/eglibc/+bug/1253638
            ${_target} PROPERTIES
            LINK_FLAGS "-Wl,-fuse-ld=gold,--disable-new-dtags,--rpath='$ORIGIN'"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/MasterDebug${_subdir}"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/MasterRelease${_subdir}"
            LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/MasterMinSizeRel${_subdir}"
            LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/MasterRelWithDebInfo${_subdir}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Master${CMAKE_BUILD_TYPE}${_subdir}"
    )
endif()
list(APPEND OUTPUT_TO_MASTER_TARGETS ObjectDetection)
set(
        OUTPUT_TO_MASTER_TARGETS "${OUTPUT_TO_MASTER_TARGETS}"
        CACHE INTERNAL "List of targets to output to Master* dirs" FORCE
)