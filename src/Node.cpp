//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Node.h"


Node::Node()
{
    mPrev = nullptr;
    mCost = 0;
}

Node::Node(const std::string& pName, Coordinate* pCoordinate)
    : mName(pName)
    , mCoord(pCoordinate)
{ }

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

Coordinate* Node::getCoord() {
    return mCoord;
}

void Node::setName(std::string &pName) {
    mName = pName;
}

void Node::addAdjacencyList(Edge *pEdge) {
    mAdjacencyList.push_back(pEdge);
}

void Node::setPrev(Node *pNode) {
    mPrev = pNode;
}

void Node::setCost(double pCost) {
    mCost = pCost;
}

void Node::setCoord(Coordinate *pCoord) {
    mCoord = pCoord;
}