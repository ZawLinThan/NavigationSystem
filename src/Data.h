#pragma once

#include "Graph.h"
#include "stringSlicing.h"
#include <unordered_set>
#include <functional>
#include <list>

const double PI = 3.1415;

// custom comparator with a functor for priority queue
struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->getCost() + a->getH()> b->getCost() + b->getH(); // Min-heap (smallest value on top) // sort based on total value (cost + H)
    }
};

class Data{
public:
    // parametrized constructor
    Data(const std::string& pFile);

    // assign heuristic value to each node
    void assignHeuristic(Node* pEndNode);

    // check if the node is in the closed set or not (for efficiency, not to repeat the visited, guaranteed node)
    bool closedSetCheck(Edge* node);

    // check if the node is in the open set or not (not to put the node replicas in open set)
    bool openSetCheck(Edge* node);

    // if the path is found, retrieve the path and print it out
    void printPath(Node* pEndNode);

    // find the path and cost for destination using Dijkstra algorithm
    void findPath(const std::string& pStart, const std::string& pEnd);

    // helper function for path finding
    void findPathHelper(Node* pStartNode, Node* pEndNode);

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
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet; // priority queue for minimum cost
    //std::list<Node*> openSet;
};

// convert degree to radian
double degreeToRadian(double pDegree);

// create heuristic value between 2 nodes
// helper function of assignHeuristic() function
double getHeuristic(Coordinate* pFrom, Coordinate* pTo);