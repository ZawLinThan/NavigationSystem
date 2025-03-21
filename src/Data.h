#pragma once

#include "Graph.h"
#include "stringSlicing.h"
#include <unordered_set>
#include <functional>

// custom comparator with a functor
struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->getCost() > b->getCost(); // Min-heap (smallest value on top)
    }
};

class Data{
public:
    Data(const std::string& pFile);

    void findPath(const std::string& pStart, const std::string& pEnd);

    // return the unordered-map for testing
    // test if the nodes are created well
    Graph testFunctionData();

    bool closedSetCheck(Edge* node);

    ~Data();
private:
    Graph mGraph;
    std::unordered_set<Node*> closedSet; // hashset for O(1) lookup
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
};