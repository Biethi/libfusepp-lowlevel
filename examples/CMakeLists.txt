cmake_minimum_required(VERSION 3.10)

project(fusepp-lowlevel-examples LANGUAGES CXX)

add_executable(test_fuse_low_level)

set_target_properties(test_fuse_low_level PROPERTIES COMPILE_FLAGS -D_FILE_OFFSET_BITS=64 )
set_property(TARGET test_fuse_low_level PROPERTY CXX_STANDARD 17)

target_sources(test_fuse_low_level PRIVATE
    HelloFS.cpp
    fuse_test_main.cpp
)

target_link_libraries(test_fuse_low_level PRIVATE
    fuse
    fusepp-lowlevel
    pthread
)