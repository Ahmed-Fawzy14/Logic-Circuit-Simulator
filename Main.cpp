#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Logic_Gate.cpp"
using namespace std;

int main()
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


    return 0;
}