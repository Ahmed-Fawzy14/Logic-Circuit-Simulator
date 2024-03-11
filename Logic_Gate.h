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

    //Funcitons

    void sort_Cir_inputs();




    // Setters
    void setName(const string& name) {
        this->name = name;
    }

    void setNumOfInputs(int num_Of_Inputs) {
        this->num_Of_Inputs = num_Of_Inputs;
    }

    void setDelayPs(int delay_ps) {
        this->delay_ps = delay_ps;
    }

    void setExpression(const vector<string>& expression) {
        this->expression = expression;
    }

    void setCirInputs(const vector<tuple<char, bool, int>>& cirInputs) {
        this->cirInputs = cirInputs;
    }

    void setCirCompName(const string& cirCompName) {
        this->cirCompName = cirCompName;
    }

    void setCirOutput(bool cirOutput) {
        this->cirOutput = cirOutput;
    }

    void setCirType(const string& cirType) {
        this->cirType = cirType;
    }

    // Getters
    string getName() const {
        return name;
    }

    int getNumOfInputs() const {
        return num_Of_Inputs;
    }

    int getDelayPs() const {
        return delay_ps;
    }

    vector<string> getExpression() const {
        return expression;
    }

    vector<tuple<char, bool, int>> getCirInputs() const {
        return cirInputs;
    }

    string getCirCompName() const {
        return cirCompName;
    }

    bool getCirOutput() const {
        return cirOutput;
    }

    string getCirType() const {
        return cirType;
    }



};


#endif //LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
