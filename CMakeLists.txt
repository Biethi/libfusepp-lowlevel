cmake_minimum_required(VERSION 3.10)

project(fusepp-lowlevel LANGUAGES C CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ./
)

add_subdirectory(examples)
