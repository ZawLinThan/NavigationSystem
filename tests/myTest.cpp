#define CONFIG_CATCH_MAIN

#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "stringSlicing.h"
#include "Data.h"

TEST_CASE("Testing")
{
    SECTION("Slice String")
    {
        // Test if the string is sliced correctly
        std::string str = "Mandalay|5";
        std::vector<std::string> vec = stringSlice(str, '|');

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == "Mandalay");
        REQUIRE(vec[1] == "5");
    }

    SECTION("Creating graph")
    {
        Data data("/Users/zawlinthan/Desktop/NavigationSystem/NavigationSystem/testData.txt");
        std::unordered_map<std::string, Node*> mp = data.getGraph().getMap();

        // test the first node
        auto temp1 = mp.at("Yangon");

        auto tempAdjacency1 = temp1->getAdjacencyList();
        std::vector<std::string> adjacencyList1 = {"Mandalay", "Naypyitaw", "Bago"};
        std::vector<double> costList1 = {5,1, 2};

        for (int i = 0; i < 2; ++i)
        {
            // check the name of city in the adjacency list
            REQUIRE(adjacencyList1[i] == tempAdjacency1[i]->mTo->getName());
            // check the cost to cities in the adjacency list
            REQUIRE(costList1[i] == tempAdjacency1[i]->mCost);
        }

        // test the second node
        auto temp2 = mp.at("Naypyitaw");
        auto tempAdjacency2 = temp2->getAdjacencyList();
        std::vector<std::string> adjacencyList2 = {"Yangon", "Mandalay", "Bago", "Taunggyi"};
        std::vector<double> costList2 = {1,3,2,3};

        for (int i = 0; i < 3; ++i)
        {
            // check the name of city in the adjacency list
            REQUIRE(adjacencyList2[i] == tempAdjacency2[i]->mTo->getName());
            // check the cost to cities in the adjacency list
            REQUIRE(costList2[i] == tempAdjacency2[i]->mCost);
        }
    }

    SECTION("Dijkstra")
    {
        Data data("/Users/zawlinthan/Desktop/NavigationSystem/NavigationSystem/testData.txt");
        data.findPath("Yangon", "Mandalay");
        // to output : Yangon -> Bago -> Mawlamyine, cost: 5
        data.findPath("Yangon", "Mandalay");
    }
}
