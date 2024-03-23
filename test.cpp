
#include "Logic_Gate.h"
#include "circuit.h"
// #include "NewCircuit.cpp"
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <cassert>
using namespace std;

void printVectorBeforeSorting(const std::vector<std::tuple<std::string, bool, int>> &vec)
{
    for (const auto &item : vec)
    {
        std::cout << "Input: " << std::get<0>(item)
                  << ", Value: " << (std::get<1>(item) ? "true" : "false")
                  << ", Timestamp: " << std::get<2>(item) << '\n';
    }
}

