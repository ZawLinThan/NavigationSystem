//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Data.h"
#include <iostream>

Data::Data(const std::string& pFile)
{
    std::ifstream ifs(pFile);

    if (ifs.is_open())
    {
        std::string str;        // var to store str from the file
        std::string rootCity;   // var to store the root city
        double cost;            // var to store each cost to the other city
        Node* rootNode;         // var for the node of root city
        Node* adjacentNode;     // var for the node of adjacency list for root city

        while(!ifs.eof())
        {
            std::getline(ifs,str);
            if (str.find("City:") == 0)
            {
                rootCity = str.substr(5);
                rootNode = mGraph.getNode(rootCity);

            } else {
                std::vector<std::string> sliceStrVec = stringSlice(str, '|');
                adjacentNode = mGraph.getNode(sliceStrVec[0]);
                cost = stof(sliceStrVec[1]);

                mGraph.createEdge(rootNode, adjacentNode, cost);
            }
        }
    } else {
        throw std::invalid_argument("Invalid file name");
    }
}

bool Data::closedSetCheck(Edge* edge)
{
    if (closedSet.find(edge->mTo) != closedSet.end())
    {
        return true;
    } else {
        return false;
    }
}

void Data::findPath(const std::string& pStart, const std::string& pEnd)
{
    // Reverse the start and end b/c dikjstra gives the reverse path
    Node* startNode = mGraph.getNode(pStart);
    Node* endNode = mGraph.getNode(pEnd);

    // put the start node to the closed set
    closedSet.insert(startNode);
    // set current node to startNode
    Node* currentNode = startNode;

    do {
        // get the adjacency list
        std::vector<Edge*> adjacencyList = currentNode->getAdjacencyList();

        // Iterate through adjacency list of the node
        for (auto& i : adjacencyList)
        {
            // if not in closed set
            if (!closedSetCheck(i))
            {
                // if previous node is empty / the node is not visited yet
                if (i->mTo->getPrev() == nullptr)
                {
                    // set previous node to be the current node
                    i->mTo->setPrev(currentNode);
                    // set the cost
                    i->mTo->setCost(currentNode->getCost());
                    // add the node to the open set
                    openSet.push(i->mTo);
                } else {
                // if previous node has data / the node is visited
                }
            }
        }

        // if open set is empty, no path is found
        if (openSet.empty())
        {
            break;
        }

        currentNode = openSet.top();

    } while (currentNode != endNode);
}

Graph Data::testFunctionData()
{
    return mGraph;
}

Data::~Data()
{
    for (auto& i : mGraph.testFunctionGraph())
    {
        delete i.second;
    }
}