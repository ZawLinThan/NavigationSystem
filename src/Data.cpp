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
            // check if the city is the root city or the adjacent city
            if (str.find("City:") == 0)
            {
                // if it is root city, slice it (to remove "City:" from the line)
                rootCity = str.substr(5);
                // create/ get node for the root city
                rootNode = mGraph.getNode(rootCity);

            } else {
                // check if the string is the blank line
                if (!str.empty())
                {
                    // slice string to get the city name and cost to the city
                    std::vector<std::string> sliceStrVec = stringSlice(str, '|');
                    // create/ get node for the adjacent node
                    adjacentNode = mGraph.getNode(sliceStrVec[0]);
                    // get cost for the city
                    cost = stof(sliceStrVec[1]);

                    // create the edge from the root city to the adjacent city and set the cost
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

    // bool variable to check if the path is found or not
    bool flag = true;

    // start the main do-while loop
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
                        // if new path is better, set the previous node of the city to the current node
                        i->mTo->setPrev(currentNode);
                        // recalculate the cost
                        i->mTo->setCost(currentNode->getCost() + i->mCost);
                    }
                }
            }
        }

        // if open set is empty, no path is found
        if (openSet.empty())
        {
            std::cout << "No path is found" << std::endl;
            // flag is set to "false" for not to output the data after the loop
            flag = false;
            break;
        }

        // Reset the current node  to nullptr and set cost to 0 for next cycle
        currentNode->setPrev(nullptr);
        currentNode->setCost(0);

        // update the current node to the smallest-distance adjacent city
        currentNode = openSet.top();
        // remove the node from the open set
        openSet.pop();

    } while (currentNode != endNode);


    if (flag)
    {
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
        std::cout << temp->getName() << std::endl;
    }

    // Reset the current node (the last node) to nullptr and set cost to 0 for next cycle
    currentNode->setPrev(nullptr);
    currentNode->setCost(0);

    // delete all data in open set and closed set
    // reset the node ptr and cost of the data in each set
    deleteOpenSet();
    deleteClosedSet();
}

void Data::deleteClosedSet()
{
    closedSet.clear();
}

void Data::deleteOpenSet()
{
    // remove all items in the open set
    while (!openSet.empty())
    {
        // get the item on the top
        auto temp = openSet.top();

        // reset the previous node and cost
        temp->setPrev(nullptr);
        temp->setCost(0);

        // remove the item on the top
        openSet.pop();
    }

}

Graph Data::getGraph() {
    return mGraph;
}

Data::~Data()
{
    // free the memory for all pointers in the graph
    for (auto& i : mGraph.getMap())
    {
        delete i.second;
    }
}
