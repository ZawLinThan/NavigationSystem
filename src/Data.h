#pragma once

#include "Graph.h"
#include "stringSlicing.h"

class Data{
public:
    Data(const std::string& pFile);
    void createGraph(const std::string& pStart, const std::string& pEnd);

    // return the unordered-map for testing
    // test if the nodes are created well
    Graph testFunctionData();

    ~Data();
private:
    Graph mGraph;
};