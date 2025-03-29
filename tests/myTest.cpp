#define CONFIG_CATCH_MAIN

#include <iostream>
#include "catch.hpp"
#include "stringSlicing.h"
#include "Data.h"

TEST_CASE("Slice String")
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
}

TEST_CASE("Data class")
{
    SECTION("Creating graph")
    {
        Data data("../data/testData.txt");
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
        std::vector<std::string> adjacencyList2 = {"Yangon", "Mandalay", "Bago", "Pyinmana"};
        std::vector<double> costList2 = {1,4,1.41,2};

        for (int i = 0; i < 4; ++i)
        {
            // check the name of city in the adjacency list
            REQUIRE(adjacencyList2[i] == tempAdjacency2[i]->mTo->getName());
            // check the cost to cities in the adjacency list
            REQUIRE((int)costList2[i] == (int)tempAdjacency2[i]->mCost);
        }
    }

    SECTION("Test Degree to Radian")
    {
        REQUIRE(degreeToRadian(180) == PI);
    }

    SECTION("Get Heuristic")
    {
        auto* firstCoord = new Coordinate(0,0);

        auto* secCoord = new Coordinate(3,4);

        auto* thirdCoord = new Coordinate(1,2);
        // distance between first and second nodes has to be larger than that of first and third nodes.
        REQUIRE(getHeuristic(firstCoord, secCoord) > getHeuristic(firstCoord,thirdCoord));
    }

    SECTION("A*")
    {
        Data data("../data/testData.txt");
        // Yangon -> Mandalay, cost: 5
        // Yangon -> Naypyitaw -> Mandalay, cost : 5
        data.findPath("Yangon", "Mandalay");

        // Yangon -> Mandalay -> Taunggyi, cost : 9
        data.findPath("Yangon", "Taunggyi");

        data.findPath("Naypyitaw", "Naypyitaw");

        // to output : Yangon -> Bago -> Mawlamyine, cost: 5
        data.findPath("Bago", "Kalaw");
    }
}
