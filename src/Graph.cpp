//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Graph.h"

Node *Graph::getNode(const std::string& pName)
{
    if(mNodeMap.find(pName) != mNodeMap.end())
    {
        return mNodeMap[pName];
    } else {
        Node* node = new Node(pName);
        mNodeMap.insert(std::make_pair(pName,node));
        return node;
    }
}

std::unordered_map<std::string, Node*> Graph::testFunctionGraph()
{
    return mNodeMap;
}
