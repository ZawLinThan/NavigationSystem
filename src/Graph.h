#pragma once
#include <fstream>
#include <unordered_map>

struct Node{
    // Name of the node
    std::string mName;

    // Adjacency list
    std::vector<Node*> mAdjacencyList;
    std::vector<double> mCostList;

    // Path list
    std::vector<std::string> mPath;

    // Track whether the node has been visited or not
    bool mVisited;

    // Default Constructor
    Node()
    {
        mVisited = false;
    }

    Node(const std::string& pName)
    {
        mName = pName;
        mVisited = false;
    }

};

struct Edge{
    Node* from;
    Node* to;
    double cost;
};


class Graph{
public:
    Node* getNode(const std::string& pName);

    // return the unordered-map for testing
    // test if the nodes are created well
    std::unordered_map<std::string, Node*> testFunctionGraph();
private:
    std::unordered_map<std::string, Node*> mNodeMap;
};