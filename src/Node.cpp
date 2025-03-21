//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Node.h"


Node::Node()
{
    mVisited = false;
}

Node::Node(const std::string& pName)
{
    mName = pName;
    mVisited = false;
}

std::string Node::getName() {
    return mName;
}

std::vector<Edge*> Node::getAdjacencyList() {
    return mAdjacencyList;
}

void Node::setName(std::string &pName)
{
    mName = pName;
}

void Node::addAdjacencyList(Edge *pEdge)
{
    mAdjacencyList.push_back(pEdge);
}


void Node::addPath(std::string &pPath)
{

}

void Node::setVisited(bool flag)
{
    mVisited = flag;
}