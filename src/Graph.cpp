//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Graph.h"
#include <iostream>
#include <cstdlib>

Node* Graph::getNode(const std::string& pName)
{
    if(mNodeMap.find(pName) != mNodeMap.end())
    {
        return mNodeMap[pName];
    } else {
        class Node* node = new Node(pName);
        mNodeMap.emplace(pName,node);
        return node;
    }
}

void Graph::createEdge(Node *pFrom, Node *pTo, double pCost)
{
    // check if the root node is null
    if (pFrom == NULL) {
        std::cout << "Root city node is empty";
        exit(1);
    }
    // check if the adjacent node is null
    if (pTo == NULL) {
        std::cout << "City to be added to the adjacency list is empty";
        exit(1);
    }

    // create an edge from root to adjacent city and push-back it into root node's adjacent list
    Edge* fromRootEdge = new Edge(pTo,pCost);

    pFrom->addAdjacencyList(fromRootEdge);
}

std::unordered_map<std::string, Node*> Graph::testFunctionGraph()
{
    return mNodeMap;
}
