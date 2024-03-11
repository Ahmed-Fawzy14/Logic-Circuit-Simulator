//
// Created by Fawzy on 3/7/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
#define LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
using namespace std;
#include <string>
#include <vector>
#include <tuple>


class Logic_Gate {
private:

    //data from .lib file

    //Name as string from .lib file
    string name;

    //Number of inputs as from .lib file
    int num_Of_Inputs = 0;

    //Delay in picoseconds as in .lib file
    int delay_ps = 0;

    //Expression as in .lib file split into the following format:
    //input, operator, input, operator, input... so the odd index is always an operator
    vector<string> expression;

    //The logic gate that will be used will have the following data elements used


    //Will be filled with data from the .stim file
    //The tuple is formatted as follows: Input name, Logic Value, Propagation Delay
    vector<tuple<char, bool, int>> cirInputs;

    //Name as in .cir file
    string cirCompName;

    //Initialized as 0
    bool cirOutput = 0;

    //Will take the same value as name
    string cirType;

public:

    Logic_Gate()
    {

    }

    Logic_Gate(string name, int num_Of_Inputs, int delay_ps, vector<string> expression)
    {
        this->name = name;
        this->num_Of_Inputs = num_Of_Inputs;
        this->delay_ps = delay_ps;
        this->expression = expression;
        cirCompName = "Unnamed";
        cirType = "No Type";

    }



};


#endif //LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
