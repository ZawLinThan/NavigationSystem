#pragma once

#include "Graph.h"
#include "stringSlicing.h"
#include <unordered_set>
#include <functional>
#include <list>

// custom comparator with a functor for priority queue
struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->getCost() > b->getCost(); // Min-heap (smallest value on top)
    }
};

class Data{
public:
    // parametrized constructor
    Data(const std::string& pFile);

    double getHeuristic(Coordinate* pFrom, Coordinate* pTo);

    // helper function for path finding
    void findPathHelper(Node* pStartNode, Node* pEndNode);

    // find the path and cost for destination using Dijkstra algorithm
    void findPath(const std::string& pStart, const std::string& pEnd);

    // check if the node is in the closed set or not (used for Dijkstra algorithm)
    bool closedSetCheck(Edge* node);

    // delete all items in the closed set
    void deleteClosedSet();

    // delete all items in open set
    // reset the cost of each item to 0
    // reset the previous node of each item to nullptr
    void deleteOpenSet();

    // return the graph for testing
    Graph getGraph();

    // destructor to free memory
    ~Data();
private:
    Graph mGraph;
    std::unordered_set<Node*> closedSet; // hashset for O(1) lookup
    //std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet; // priority queue for minimum cost
    std::list<Node*> openSet;
};