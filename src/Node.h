#include <string>
#include <vector>
#include "Edge.h"

class Node{
private:
    // Name of the node
    std::string mName;

    // Adjacency list
    std::vector<Edge*> mAdjacencyList;

    // total cost, up to this node
    unsigned mCost;

    // previous node (to store path information)
    Node* mPrev;
public:
    // Constructors
    Node();
    Node(const std::string& pName);


    // Getters
    std::string getName();
    std::vector<Edge*> getAdjacencyList();
    Node* getPrev();
    double getCost();

    // Setters
    void setName(std::string& pName);
    void addAdjacencyList(Edge* pEdge);
    void setPrev(Node* pNode);
    void setCost(double pCost);
};
