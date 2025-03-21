//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Node.h"


Node::Node()
{
    mVisited = false;
    mPrev = nullptr;
    mCost = 0;
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

Node* Node::getPrev() {
    return mPrev;
}

double Node::getCost() {
    return mCost;
}

void Node::setName(std::string &pName) {
    mName = pName;
}

void Node::addAdjacencyList(Edge *pEdge) {
    mAdjacencyList.push_back(pEdge);
}


void Node::addPath(std::string &pPath) {

}

void Node::setVisited(bool flag) {
    mVisited = flag;
}

void Node::setPrev(Node *pNode) {
    mPrev = pNode;
}

void Node::setCost(double pCost) {
    mCost = pCost;
}