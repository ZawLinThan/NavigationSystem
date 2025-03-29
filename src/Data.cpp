//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Data.h"
#include <iostream>
#include <cmath>
#include <stack>

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

void Data::assignHeuristic(Node *pEndNode) {
    // iterate through the map
    for (auto i : mGraph.getMap())
    {
        // if the node has not assigned the heuristic value
        if (i.second->getH() == 0)
        {
            // assign the heuristic value to that node
            i.second->setH(getHeuristic(i.second->getCoord(), pEndNode->getCoord()));
        }
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


bool Data::openSetCheck(Edge *edge) {
    auto temp = openSet;
    while (!temp.empty())
    {
        // if the city in the open set is equal to the node
        // return true
        if (temp.top() == edge->mTo)
        {
            return true;
        }
        temp.pop();
    }
    // if 'true' is not returned, not found
    // return false
    return false;
}


void Data::printPath(Node* pEndNode)
{
    std::cout << "Path found, cost : " << pEndNode->getCost() << std::endl;

    auto temp = pEndNode;    // initialized to retrieve the path backward
    std::stack<Node*> path;         // to store the path is backward direction
    while (temp!= nullptr)
    {
        // add the path to the stack
        path.push(temp);
        temp = temp->getPrev();
    }

    // print the city out
    while (!path.empty())
    {
        temp = path.top();
        if (path.size() != 1)
        {
            std::cout << temp << " -> ";
        } else {
            std::cout << temp << std::endl << std::endl;
        }
        path.pop();
    }
}


void Data::findPathHelper(Node* pStartNode, Node* pEndNode) {
    Node* currentNode = pStartNode;

    // flag var to check if the path is found or not
    bool flag = true;

    // while current node is not equal to the destination node
    while (currentNode != pEndNode)
    {
        // put the current node to the closed set
        closedSet.insert(currentNode);

        // set size to the size of open set for
        unsigned size = openSet.size();

        // traverse through the adjacency list of current node
        for (auto i : currentNode->getAdjacencyList())
        {
            if (closedSetCheck(i) == false)
            {
                // if the node's prev is null
                if (i->mTo->getPrev() == nullptr)
                {
                    // set its prev to curr node
                    i->mTo->setPrev(currentNode);
                    // set its total cost
                    i->mTo->setCost(i->mCost + currentNode->getCost());
                    // update the F of the node
                    i->mTo->setF();
                } else {
                    // check if the new path is superior
                    if (currentNode->getCost() + i->mTo->getH() + i->mCost < i ->mTo->getF())
                    {
                        // set prev to current node
                        i -> mTo->setPrev(currentNode);
                        // recalculate the cost (path cost + node's cost)
                        i->mTo->setCost(currentNode->getCost() + i->mCost);
                        // update the F of the node
                        i->mTo->setF();
                    }
                }
                // if the node is not in open set, push back
                // if statement to prevent duplicates
                if (openSetCheck(i) == false)
                {
                    // add the node to the open set
                    openSet.push(i->mTo);
                }
            }
        }

        // if open set is empty, no path is found
        if (openSet.empty()) {
            // set flag to false
            flag = false;
            std::cout << "No path found" << std::endl << std::endl;
            break;
        }

        // if new node is added in this cycle, set its prev to current node
        if (openSet.size() != size)
        {
            // set the previous of the next nearest node be the current node
            openSet.top()->setPrev(currentNode);
        }

        // set the current node the next nearest node / top node from the open set
        currentNode = openSet.top();

        // remove the top item from the open set / remove the next nearest node
        openSet.pop();
    }

    // path is found
    if (flag)
    {
        printPath(pEndNode);
    }

}

void Data::findPath(const std::string& pStart, const std::string& pEnd)
{
    // get the start node
    Node* startNode = mGraph.findNode(pStart);
    // get the end node
    Node* endNode = mGraph.findNode(pEnd);

    // if the start node and end node exist
    if (startNode && endNode)
    {
        // create and assign heuristic value to each node
        assignHeuristic(endNode);
        // Reverse the start and end b/c dijkstra gives the reverse path
        findPathHelper( startNode, endNode);
    }

    // if the start node does not exist
    if (startNode == nullptr)
    {
        std::cout << "First city name does not exist" << std::endl;
    }
    // if the end node does not exist
    if (endNode == nullptr){
        std::cout << "Second city name does not exist" << std::endl;
    }

    // Reset prev and cost for next cycle
    for (auto i : mGraph.getMap())
    {
        // reset prev
        i.second->setPrev(nullptr);
        // reset cost
        i.second->setCost(0);
        // reset heuristic
        i.second->setH(0);
        // update F again
        i.second->setF();
    }

    // Remove all items in both sets for next cycle
    deleteClosedSet();
    deleteOpenSet();
}


void Data::deleteClosedSet()
{
    // clear closed set
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
        // delete the coordinate struct of the node
        delete i.second->getCoord();
        // delete the node itself
        delete i.second;
    }
}

double degreeToRadian(double pDegree) {
    return pDegree * PI / 180;
}

double getHeuristic(Coordinate *pFrom, Coordinate *pTo)
{

    // get heuristic value
    // Haversine formula
    double latFrom, latTo, longFrom, longTo;
    latFrom = degreeToRadian(pFrom->mLatitude);
    longFrom = degreeToRadian(pFrom->mLongitude);
    latTo = degreeToRadian(pTo->mLatitude);
    longTo = degreeToRadian(pTo->mLongitude);

    double dLat = latFrom - latTo;
    double dLong = longFrom - longTo;

    // using Haversine Heuristic function,
    double a = pow(sin(dLat/2),2) + (cos(latFrom) * cos(latTo) * pow(sin(dLong/2),2));
    double value = 2 * 6371 * asin(sqrt(a));  //  6371 is the earth radius

    return value;
}