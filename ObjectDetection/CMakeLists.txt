cmake_minimum_required(VERSION 3.19)
project(ObjectDetection)

set(SOURCE Preprocessing.h Preprocessing.cpp)
add_library(ObjectDetection SHARED ${SOURCE})

set_target_properties(ObjectDetection PROPERTIES FOLDER "Libraries")