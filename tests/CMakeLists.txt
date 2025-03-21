# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)


set(HEADER_FILES
        catch.hpp
)

set(SOURCE_FILES
        catch.cpp
        myTest.cpp
)

add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests src)