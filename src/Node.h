#include <string>
#include <vector>
#include "Edge.h"

class Node{
private:
    // Name of the node
    std::string mName;

    // Adjacency list
    std::vector<Edge*> mAdjacencyList;


    // Path list
    std::vector<std::string> mPath;

    // Track whether the node has been visited or not
    bool mVisited;
public:
    // Default Constructor
    Node();

    // parametrized constructor
    Node(const std::string& pName);

    // total cost, up to this node
    double mCost;

    // previous node (to store path information)
    Node* mPrev;

    // Getters
    std::string getName();
    std::vector<Edge*> getAdjacencyList();
    std::vector<std::string> getPath();
    bool getVisited();

    // Setters
    void setName(std::string& pName);
    void addAdjacencyList(Edge* pEdge);
    void addPath(std::string& pPath);
    void setVisited(bool flag);
};
