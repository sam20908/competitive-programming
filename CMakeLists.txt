cmake_minimum_required(VERSION 4.0)
project(competitive-programming CXX)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory("test")
endif()
