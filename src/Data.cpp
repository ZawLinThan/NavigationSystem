//
// Created by Zaw Lin Than on 3/19/25.
//

#include "Data.h"

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

Graph Data::testFunctionData()
{
    return mGraph;
}

void Data::createGraph(const std::string& pStart, const std::string& pEnd)
{
    Node* startNode = mGraph.getNode(pStart);
    Node* endNode = mGraph.getNode(pEnd);

}
