# Require CMAKE 3.1 or higher
cmake_minimum_required(VERSION 3.12)

# If you create new headers files, add them to these list!
set(HEADER_FILES
        Data.h
        Graph.h
        Node.h
        stringSlicing.h
)

# If you create new cpp files, add them to these list!
set(SOURCE_FILES
        Data.cpp
        Graph.cpp
        Node.cpp
        stringSlicing.cpp
        Edge.h
)

# Don't change this
add_library(src ${SOURCE_FILES} ${HEADER_FILES})
