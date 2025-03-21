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
        for (auto i : vec) {std::cout << i << "\n";}
    }

    SECTION("Creating graph")
    {
        Data data("/Users/zawlinthan/Downloads/NavigationSystem/testData.txt");
        std::unordered_map<std::string, Node*> mp = data.testFunctionData().testFunctionGraph();

        auto temp1 = mp.at("Yangon");
        REQUIRE(temp1->mName == "Yangon");

        auto tempAdjacency1 = temp1->mAdjacencyList;
        auto tempCostList1 = temp1->mCostList;
        std::vector<std::string> adjacencyList1 = {"Mandalay", "Naypyitaw"};
        std::vector<double> costList1 = {5,1};

        for (int i = 0; i < 2; ++i)
        {
            REQUIRE(adjacencyList1[i] == tempAdjacency1[i]->mName);
            REQUIRE(costList1[i] == tempCostList1[i]);
        }

        auto temp2 = mp.at("Naypyitaw");
        auto tempAdjacency2 = temp2->mAdjacencyList;
        auto tempCostList2 = temp2->mCostList;
        std::vector<std::string> adjacencyList2 = {"Yangon", "Mandalay", "Lashio"};
        std::vector<double> costList2 = {1,2,3};

        for (int i = 0; i < 3; ++i)
        {
            REQUIRE(adjacencyList2[i] == tempAdjacency2[i]->mName);
            REQUIRE(costList2[i] == tempCostList2[i]);
        }
    }
}
