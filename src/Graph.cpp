//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Graph.h"
#include <iostream>
#include <cstdlib>

Node* Graph::getNode(const std::string& pName, Coordinate* pCoordinate)
{
    // if the node is in the NodeMap
    if(mNodeHashMap.find(pName) != mNodeHashMap.end())
    {
        // return the existing node
        return mNodeHashMap[pName];
    } else {
        // else create a new node
        class Node* node = new Node(pName, pCoordinate);
        // add the node to the map and return the new node
        mNodeHashMap.emplace(pName,node);
        return node;
    }
}

Node* Graph::findNode(const std::string &pName)
{
    // if the node is in the NodeMap
    if(mNodeHashMap.find(pName) != mNodeHashMap.end()) {
        // return the existing node
        return mNodeHashMap[pName];
    } else {
        // else return nullptr
        return nullptr;
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

    // add the edge to the root city's adjacency list
    pFrom->addAdjacencyList(fromRootEdge);
}

std::unordered_map<std::string, Node*> Graph::getMap()
{
    return mNodeHashMap;
}
