//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Graph.h"
#include <iostream>

Node* Graph::getNode(const std::string& pName)
{
    if(mNodeMap.find(pName) != mNodeMap.end())
    {
        return mNodeMap[pName];
    } else {
        Node* node = new Node(pName);
        mNodeMap.emplace(pName,node);
        return node;
    }
}

void Graph::createEdge(Node *pFrom, Node *pTo, double pCost)
{
    // check if the root node is null
    if (pFrom == NULL) {std::cerr << "Root city node is empty";}
    // check if the adjacent node is null
    if (pTo == NULL) {std::cerr << "City to be added to the adjacency list is empty";}

    // create an edge from root to adjacent city and push-back it into root node's adjacent list
    Edge* fromRootEdge = new Edge(pTo,pCost);
    pFrom->mAdjacencyList.push_back(fromRootEdge);

    // create an edge from adjacent city to root city and push-back it into adjacent-city node's adjacent list
    /*Edge* toRootEdge = new Edge(pFrom, pCost);
    pTo->mAdjacencyList.push_back(toRootEdge);*/
}

std::unordered_map<std::string, Node*> Graph::testFunctionGraph()
{
    return mNodeMap;
}
