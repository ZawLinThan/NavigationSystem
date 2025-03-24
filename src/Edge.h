#pragma once

struct Edge{
    class Node* mTo;
    double mCost;

    Edge()
    {
        mTo = nullptr;
        mCost = 0;
    }

    Edge(Node* pNode, double pCost)
    {
        mTo = pNode;
        mCost = pCost;
    }
};