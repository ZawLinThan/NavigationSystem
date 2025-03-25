//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Data.h"
#include <iostream>
#include <math.h>

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
        std::vector<std::string> sliceStrVec;
        while(!ifs.eof())
        {
            std::getline(ifs,str);
            // check if the city is the root city or the adjacent city
            if (str.find("City:") == 0)
            {
                // if it is root city, slice it (also remove "City:" from the line)
                sliceStrVec = stringSlice(str.substr(5), '|');

                // first index is the name of the city
                rootCity = sliceStrVec[0];

                // create/ get node for the root city
                rootNode = mGraph.getNode(rootCity, new Coordinate (stof(sliceStrVec[1]),stof(sliceStrVec[2])));

            } else {
                // check if the string is the blank line
                if (!str.empty())
                {
                    // slice string to get the city name and cost to the city
                    sliceStrVec = stringSlice(str, '|');
                    // create/ get node for the adjacent node with the city name and the city's coordinate
                    adjacentNode = mGraph.getNode(sliceStrVec[0], new Coordinate (stof(sliceStrVec[2]),stof(sliceStrVec[3])));
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

double Data::getHeuristic(Coordinate *pFrom, Coordinate *pTo)
{
    // get heuristic value
    double value = sqrt(pow((pFrom->mLatitude-pTo->mLatitude),2) + pow((pFrom->mLongitude-pTo->mLongitude),2));
    return value;
}

void Data::findPathHelper(const std::string &pStart, const std::string &pEnd
                          , Node* pStartNode, Node* pEndNode) {
    // put the start node to the closed set
    closedSet.insert(pStartNode);
    // set current node to startNode
    Node* currentNode = pStartNode;

    // bool variable to check if the path is found or not
    bool flag = true;

    // var to store the node overall shortest cost
    Edge* minEdge;
    double totalCostMin;
    // start the main do-while loop
    do {
        // get the adjacency list
        std::vector<Edge*> adjacencyList = currentNode->getAdjacencyList();

        if (!adjacencyList.empty())
        {
            minEdge = adjacencyList[0];
            // total cost = direct distance + heuristic value
            totalCostMin = minEdge->mCost + getHeuristic(minEdge->mTo->getCoord(),pEndNode->getCoord());
        } else {
            std::cout << "ERROR -> path not found";
            break;
        }


        // Iterate through adjacency list of the node to assign prev Node and the cost
        for (auto& i : adjacencyList)
        {
            if (closedSetCheck(i) == false)
            {
                // if previous node is empty / the node is not visited yet
                if (i->mTo->getPrev() == nullptr)
                {
                    // set previous node to be the current node
                    i->mTo->setPrev(currentNode);
                    // set the cost
                    i->mTo->setCost(currentNode->getCost() + i->mCost);
                    // add the node to the open set
                    openSet.push_back(i->mTo);
                }
            }

        }

        // to find the best next node
        for (auto i : adjacencyList)
        {
            if (closedSetCheck(i) == false) {
                double totalCostCurr = i->mCost + getHeuristic(i->mTo->getCoord(), pEndNode->getCoord());

                // if previous node has data / the node is visited
                // check if the new path is  superior to the old one
                if (totalCostCurr < totalCostMin) {
                    totalCostMin = totalCostCurr;
                    minEdge = i;
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
        /*currentNode->setPrev(nullptr);
        currentNode->setCost(0)*/;

        currentNode = minEdge->mTo;
        closedSet.insert(currentNode);

    } while (currentNode != pEndNode);
    ////////// Dijkstra Algorithm Implementation /////////

    if (flag)
    {
        // output the cost of path
        std::cout << "Path found, costs : " << pEndNode->getCost() << std::endl;
        Node* temp = pEndNode;
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

void Data::findPath(const std::string& pStart, const std::string& pEnd)
{

    Node* startNode = mGraph.findNode(pStart);
    Node* endNode = mGraph.findNode(pEnd);

    if (startNode && endNode)
    {
        // Reverse the start and end b/c dijkstra gives the reverse path
        findPathHelper(pEnd, pStart, endNode, startNode);
    }

    if (startNode == nullptr)
    {
        std::cout << "First city name does not exist" << std::endl;
    }
    else if (endNode == nullptr){
        std::cout << "Second city name does not exist" << std::endl;
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
        auto temp = openSet.front();

        // reset the previous node and cost
        temp->setPrev(nullptr);
        temp->setCost(0);

        // remove the item on the top
        openSet.remove(temp);
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
