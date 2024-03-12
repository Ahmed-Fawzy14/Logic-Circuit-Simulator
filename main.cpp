#include <iostream>
#include "Logic_Gate.h"
using namespace std;

int main() {

    vector<string> testExp = {"A1", "&", "A2"};

    Logic_Gate test_Obj("test1", 2, 500, testExp);


    //Has all gate objects in .lib file
    vector<Logic_Gate> allGates;


    cout<<"Choose .lib and .cir files"<<endl;

    //upload the file

    cout<<"Choose .stim file"<<endl;

    //upload the files

    test_Obj.sort_Cir_inputs();

    for(auto x : test_Obj.getCirInputs())
    {
        cout<<get<2>(x)<<endl;
    }
    return 0;
}
