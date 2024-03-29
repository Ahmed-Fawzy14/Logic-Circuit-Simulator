// testOperator.h
#ifndef TESTOPERATOR_H
#define TESTOPERATOR_H

#include <string>
#include <stack>
#include <vector>
#include <memory>
#include "Logic_Gate.h" 
#include "circuit.h"

// Function to determine the precedence of boolean algebra operators
int precedence(char op);

// Function to apply binary operation on two operands
int applyOp(int a, int b, char op);

// Function to apply unary operation on a single operand
int applyUnaryOp(int a, char op);

// Function to replace operands in the gate's expression with their respective values
std::string replaceOperands(std::shared_ptr<Logic_Gate> gate, bool &samevalue);

// Function to perform the shunting yard algorithm on the tokenized expression
void shuntingYard(std::string &tokens, int &i, std::stack<int> &values, std::stack<char> &operators);

// Function to finalize the evaluation of the expression after applying the shunting yard algorithm
void FinishShuntingYard(std::stack<int> &numbers, std::stack<char> &operators);

// Function to evaluate the logical expression of a gate at a given time
bool evaluate(std::shared_ptr<Logic_Gate> g, int time);

// Function to find the index of a gate in the circuit's used gates based on its name
int find_usedGates_Index(circuit &c, std::string comp_Name);

// Function to calculate the new timestamp for outputs based on the current time and gate delay
int get_TimeStamp(std::shared_ptr<Logic_Gate> gate, int current_Time);

#endif //TESTOPERATOR_H
