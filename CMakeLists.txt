# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)

project(NavigationSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# source files
set(SOURCE_FILES main.cpp)

# include files
include_directories(src)

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)


add_executable(main ${SOURCE_FILES})
target_link_libraries(main src)