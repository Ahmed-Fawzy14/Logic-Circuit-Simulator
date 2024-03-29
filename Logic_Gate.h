//
// Created by Fawzy on 3/7/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
#define LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H
using namespace std;
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include<unordered_set>


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
    string expression;

    //The logic gate that will be used will have the following data elements used
    map<int, string> previousInputs;
//string is the name from the .cir file and int is initalized to -1 until .stim applies a value then we only run this again if it changes
    //Inputs ust be entered in the same order of inputs as that of the 2D vector theat you read the .cir file with
    vector<pair<string,int>> cir_Input_Names;

    //Name as in .cir file
    string cirCompName;

    string cir_Output_Name;

    //Initialized as 0
    bool cirOutput = 0;

    //Will take the same value as name
    string cirType;

public:


    Logic_Gate()
    {

    }

    Logic_Gate(string name, int num_Of_Inputs, int delay_ps, string expression)
    {
        this->name = name;
        this->num_Of_Inputs = num_Of_Inputs;
        this->delay_ps = delay_ps;
        this->expression = expression;
        cirCompName = "Unnamed";
        cirType = "No Type";
        cir_Output_Name = "no name";

    }

    //Funcitons

    // void sort_Cir_inputs(circuit c);

    std::unordered_set<std::size_t> previousInputHashes;


    map<int, string> & getPreviousInputsREF ()
    {
        return previousInputs;
    }

    void setPreviousInputs(map<int, string>  m)
    {
        this->previousInputs = m;
    }
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

    void setExpression(const string& expression) {
        this->expression = expression;
    }

//    void setCirInputs(const vector<tuple<char, bool, int>>& cirInputs) {
    //      this->cirInputs = cirInputs;
    //  }

    void setCirCompName(const string& cirCompName) {
        this->cirCompName = cirCompName;
    }


    void setCirInputName(string s, int x)
    {
        auto p = make_pair(s,x);
        cir_Input_Names.push_back(p);
    }

    void setCirOutput(bool cirOutput) {
        this->cirOutput = cirOutput;
    }

    void setCirType(const string& cirType) {
        this->cirType = cirType;
    }

    void setCirOutputName(string cir_Output_Name)
    {
        this->cir_Output_Name = cir_Output_Name;
    }

    void set_cir_Input_Names(vector<pair<string, int>> cir_Input_Names)
    {
        this->cir_Input_Names = cir_Input_Names;
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

    string getExpression() const {
        return expression;
    }


    vector<pair<string,int>> get_cir_Input_Names() const
    {
        return cir_Input_Names;
    }

    vector<pair<string,int>>& getREF_cir_Input_Names()
    {
        return this->cir_Input_Names;
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

    string getCirOutputName() const {
        return cir_Output_Name;
    }



};


#endif //LOGIC_CIRCUIT_SIMULATOR_LOGIC_GATE_H