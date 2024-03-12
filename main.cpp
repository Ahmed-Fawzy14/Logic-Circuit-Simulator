#include <iostream>
#include "Logic_Gate.h"
using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Logic_Gate.cpp"
using namespace std;

void read_lib_file()
{
    ifstream input;
    string line, name, no_of_inputs, delay, expression;
    input.open("C:/Users/Power/Desktop/Project dd1/INV, 1, ~(i1), 50.txt");
    vector <Logic_Gate> v;
    int j = 0;
    while (getline(input, line)) 
    {

    istringstream subst(line);
    getline(subst, name, ',');
    getline(subst, no_of_inputs, ',');
    getline(subst, expression, ',');
    getline(subst, delay, ',');
    vector <string> Expressions(expression.length());
    for (int i = 0; i < expression.length(); i++)
    {
        Expressions[i] = expression[i];
    }
    Logic_Gate* gate= new Logic_Gate(name, stoi(no_of_inputs), stoi(delay), Expressions);
    v.push_back(*gate);
    }    

    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] .getName() << " " << v[i] .getNumOfInputs() << " " << v[i].getDelayPs() << " ";
        for (int i = 0; i < v[i].getExpression().size(); i++)
        {
            cout << v[i].(*(getexpression()+i));
        }
    }
 
}

int main()
{
//Abdeen's Read File
    read_lib_file();
//Code from Fawzy's Main
    
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


