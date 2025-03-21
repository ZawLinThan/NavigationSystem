#cmake_minimum_required(VERSION 3.27)
#project(NavigationSystem)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(NavigationSystem main.cpp
#        src/Node.cpp
#        src/Node.h
#        src/Graph.cpp
#        src/Graph.h
#        src/Data.cpp
#        src/Data.h
#        src/stringSlicing.h
#        src/stringSlicing.cpp
#        )
#
#set(TEST_SOURCES
#        tests/myTest.cpp
#        tests/catch.hpp
#        tests/catch.cpp
#)

# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)

# Project name
project(NavigationSystem VERSION 1.0)

# Build for C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Any source files in this directory
set(SOURCE_FILES main.cpp)

# Where any include files are
include_directories(src)

# Subdirectories to build
add_subdirectory(src)
add_subdirectory(tests)

# Name of executable
add_executable(main ${SOURCE_FILES})

# Link main vs the source library
target_link_libraries(main src)