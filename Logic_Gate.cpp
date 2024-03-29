//
// Created by Fawzy on 3/7/2024.
//

#include "Logic_Gate.h"
#include "circuit.h"

#include <algorithm>
using namespace std;

// Setters
void Logic_Gate::setName(const string& name) {
    this->name = name;
}

void Logic_Gate::setNumOfInputs(int num_Of_Inputs) {
    this->num_Of_Inputs = num_Of_Inputs;
}

void Logic_Gate::setDelayPs(int delay_ps) {
    this->delay_ps = delay_ps;
}

void Logic_Gate::setExpression(const string& expression) {
    this->expression = expression;
}



void  Logic_Gate::setCirCompName(const string& cirCompName) {
    this->cirCompName = cirCompName;
}


void  Logic_Gate::setCirInputName(string s, int x)
{
    auto p = make_pair(s,x);
    cir_Input_Names.push_back(p);
}

void  Logic_Gate::setCirOutput(bool cirOutput) {
    this->cirOutput = cirOutput;
}

void  Logic_Gate::setCirType(const string& cirType) {
    this->cirType = cirType;
}

void  Logic_Gate::setCirOutputName(string cir_Output_Name)
{
    this->cir_Output_Name = cir_Output_Name;
}

void  Logic_Gate::set_cir_Input_Names(vector<pair<string, int>> cir_Input_Names)
{
    this->cir_Input_Names = cir_Input_Names;
}
// Getters
string  Logic_Gate::getName() const {
    return name;
}

int  Logic_Gate::getNumOfInputs() const {
    return num_Of_Inputs;
}

int  Logic_Gate::getDelayPs() const {
    return delay_ps;
}

string  Logic_Gate::getExpression() const {
    return expression;
}


vector<pair<string,int>>  Logic_Gate::get_cir_Input_Names() const
{
    return cir_Input_Names;
}

vector<pair<string,int>>&  Logic_Gate::getREF_cir_Input_Names()
{
    return this->cir_Input_Names;
}

string  Logic_Gate::getCirCompName() const {
    return cirCompName;
}

bool  Logic_Gate::getCirOutput() const {
    return cirOutput;
}

string  Logic_Gate::getCirType() const {
    return cirType;
}

string  Logic_Gate::getCirOutputName() const {
    return cir_Output_Name;
}
