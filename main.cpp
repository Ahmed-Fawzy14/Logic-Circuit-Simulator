#include <iostream>
#include "Logic_Gate.h"
using namespace std;

int main() {

    vector<string> testExp = {"A1", "&", "A2"};

    Logic_Gate test_Obj("test1", 2, 500, testExp);

    vector<Logic_Gate> allGates;


    return 0;
}
