#pragma once
#include <fstream>
#include <unordered_map>

struct Edge{
    struct Node* mTo;
    double mCost;

    Edge(Node* pNode, double pCost) {
        mTo = pNode;
        mCost = pCost;
    }
};

struct Node{
    // Name of the node
    std::string mName;

    // Adjacency list
    std::vector<Edge*> mAdjacencyList;
    //std::vector<double> mCostList;

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


class Graph{
public:
    // If the map does not have the node with the parameter "pName", create one
    // If it has, retrieve the existing one
    Node* getNode(const std::string& pName);

    void createEdge(Node* pFrom, Node* pTo, double pCost);
    // return the unordered-map for testing
    // test if the nodes are created well
    std::unordered_map<std::string, Node*> testFunctionGraph();
private:
    std::unordered_map<std::string, Node*> mNodeMap;
};