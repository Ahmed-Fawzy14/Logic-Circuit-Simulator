//
// Created by Fawzy on 3/16/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_TESTOPERATOR_H
#define LOGIC_CIRCUIT_SIMULATOR_TESTOPERATOR_H
#include <fstream> // Including the fstream library to read files
#include <iostream> // Including the iostream library in case of couting any output for debugging or clarity purposes
#include <string> // Including the string library to use string functions
#include <sstream> // Including the sstream library to store data from files into variables using delimiters
#include <unordered_map> // Including the unordered_map class to be used in the storing of gates
#include "circuit.h"

int run_Operator_Test(circuit &c, int current_Time, unordered_map<string, tuple <string, bool, int>> &current_Outputs_Map, int &prevInpIndex);
void input_exisits(circuit &c,  unordered_map<string, pair<bool,bool>> &flag, int &index);
int find_usedGates_Index(circuit &sample_c, string comp_Name);
int get_TimeStamp(circuit &sample_c, int current_Time, int usedGates_Index );
void insertValuesInExpression(string &tokens, vector<pair<string,int>> &cir_Input_Names, int &checkNumOfInputs);
#endif //LOGIC_CIRCUIT_SIMULATOR_TESTOPERATOR_H
