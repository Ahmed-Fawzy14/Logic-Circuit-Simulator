//
// Created by Fawzy on 3/7/2024.
//

#include "Logic_Gate.h"
#include <algorithm>
using namespace std;
//    vector<tuple<char, bool, int>> cirInputs;
void Logic_Gate::sort_Cir_inputs() {
sort(cirInputs.begin(), cirInputs.end(),
     [](const tuple<char, bool, int> &a, const tuple<char, bool, int> &b)
     {
        return (get<2>(a) < get<2>(b));
     });
}
