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
                if (!str.empty())
                {
                    std::vector<std::string> sliceStrVec = stringSlice(str, '|');
                    adjacentNode = mGraph.getNode(sliceStrVec[0]);
                    cost = stof(sliceStrVec[1]);

                    mGraph.createEdge(rootNode, adjacentNode, cost);
                }
            }
        }
    } else {
        throw std::invalid_argument("Invalid file name");
    }
}

bool Data::closedSetCheck(Edge* edge)
{
    // if found in the closed set, return true
    if (closedSet.find(edge->mTo) != closedSet.end())
    {
        return true;
    } else {
        // if not found in the closed set, return false
        return false;
    }
}

void Data::findPath(const std::string& pStart, const std::string& pEnd)
{
    // Reverse the start and end b/c dijkstra gives the reverse path
    Node* startNode = mGraph.getNode(pEnd);
    Node* endNode = mGraph.getNode(pStart);

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
                    i->mTo->setCost(currentNode->getCost() + i->mCost);
                    // add the node to the open set
                    openSet.push(i->mTo);
                } else {
                // if previous node has data / the node is visited
                    // check if the new path is  superior to the old one
                    if (currentNode->getCost() + i->mCost < i->mTo->getCost())
                    {
                        i->mTo->setPrev(currentNode);
                        i->mTo->setCost(currentNode->getCost() + i->mCost);
                    }
                }
            }
        }

        // if open set is empty, no path is found
        if (openSet.empty())
        {
            std::cout << "No path is found";
            exit(0);
        }

        currentNode = openSet.top();
        openSet.pop();

    } while (currentNode != endNode);

    // output the cost of path
    std::cout << "Path found, costs : " << endNode->getCost() << std::endl;
    Node* temp = endNode;
    // retrieving the path from previous node
    while (temp->getPrev() != nullptr)
    {
        std::cout << temp->getName() << " -> ";
        // switch to the previous node
        temp = temp->getPrev();
    }
    // output the last city
    std::cout << temp->getName();
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