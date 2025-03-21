#pragma once

struct Edge{
    class Node* mTo;
    double mCost;

    Edge(Node* pNode, double pCost) {
        mTo = pNode;
        mCost = pCost;
    }
};