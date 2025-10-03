cmake_minimum_required(VERSION 3.30)
project(competitive-programming CXX)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory("test")
endif()
