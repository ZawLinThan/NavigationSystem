#pragma once
#include <fstream>
#include <unordered_map>
#include "Node.h"

class Graph{
public:
    // If the map does not have the node with the parameter "pName", create one
    // If it has, retrieve the existing one
    Node* getNode(const std::string& pName);

    // add node to the adjacency list
    // also add the cost to the adjacent node
    void createEdge(Node* pFrom, Node* pTo, double pCost);

    // return the unordered-map for testing
    // test if the nodes are created well
    std::unordered_map<std::string, Node*> testFunctionGraph();
private:
    std::unordered_map<std::string, Node*> mNodeMap;
};