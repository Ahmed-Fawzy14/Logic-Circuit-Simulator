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

int run_Operator_Test(circuit &c, int current_Time, int &isNotReady);
void input_exisits(circuit &c, unordered_map<string, tuple <string, bool, int>> &current_Inputs_Map,  unordered_map<string, bool> &flag);
int evaluate_Expression(circuit &c, int usedGates_Index);
int find_usedGates_Index(circuit &sample_c, string comp_Name);
int get_TimeStamp(circuit &sample_c, int current_Time, int usedGates_Index );
#endif //LOGIC_CIRCUIT_SIMULATOR_TESTOPERATOR_H
