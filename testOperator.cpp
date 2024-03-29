//
// Created by Fawzy on 3/16/2024.
//
#include "testOperator.h"
#include <stack>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <functional>
#include <regex>


using namespace std;


int precedence(char op){
    if (op == '~') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0;
}

int applyOp(int a, int b, char op){
    switch(op){
        case '&': return a & b;
        case '|': return a | b;
        default: return 0;
    }
}

// Function for unary operation
int applyUnaryOp(int a, char op){
    // Directly handling '~' as logical NOT for 0 and 1
    if(op == '~'){
        return a == 0 ? 1 : 0;
    }
    return 0;
}

string replaceOperands(shared_ptr<Logic_Gate> gate, bool &samevalue)
{
    string updatedExpression = gate->getExpression();
    auto inputs = gate->get_cir_Input_Names();
    int expectedinputs = gate->getNumOfInputs();

    if (inputs.size() != expectedinputs) // makes sure the number of inputs and the size of vector are equal
    {
        cout << "number of inputs is not same as expected " << endl;
        samevalue = false;
        return "";
    }
    else
    {
        for (int i = 0; i < inputs.size(); ++i)
        {
            // Construct the operand placeholder based on input order (e.g., "i1", "i2", etc.)
            string operand = "i" + to_string(i + 1);
            string value = to_string(inputs[i].second);

            regex pattern(operand + "(\\D|$)");

            updatedExpression = regex_replace(updatedExpression, pattern, value + "$1");
        }
        return updatedExpression;
    }
}



bool evaluate(shared_ptr<Logic_Gate> g, int time){


    vector<pair<string,int>> cir_Input_Names = g->get_cir_Input_Names();
    bool samenumber = true;


    stack<int> numbers;
    //operators
    stack<char> ops;


    string tokens = replaceOperands(g, samenumber);


// The revised part of the evaluate function
    for(int i = 0; i < tokens.length(); ++i){
        if(tokens[i] == ' ') continue;

        // If token is a number
        if(isdigit(tokens[i])){
            int val = 0;
            while(i < tokens.length() && isdigit(tokens[i])){
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            numbers.push(val);
            i--; // Adjust because the for loop also increments i
        }
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
        else if(tokens[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
                int val2 = numbers.top();
                numbers.pop();

                if(ops.top() != '~'){
                    int val1 = numbers.top();
                    numbers.pop();

                    char op = ops.top();
                    ops.pop();

                    numbers.push(applyOp(val1, val2, op));
                } else {
                    // Direct application of unary operators before closing parenthesis
                    char op = ops.top();
                    ops.pop();

                    numbers.push(applyUnaryOp(val2, op));
                }
            }
            // Pop the '(' operator
            if(!ops.empty()) ops.pop();
        }
        else if(tokens[i] == '~'){
            // Push '~' onto the ops stack to signify a pending unary operation
            ops.push(tokens[i]);
        }
        else {
            // When encountering a binary operator, check the precedence and apply operations accordingly
            while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])){
                if(ops.top() == '~'){ // Handle unary operator '~' immediately
                    int val = numbers.top();
                    numbers.pop();

                    char op = ops.top();
                    ops.pop();

                    numbers.push(applyUnaryOp(val, op));
                } else { // Handle binary operators based on precedence
                    int val2 = numbers.top();
                    numbers.pop();

                    if(!numbers.empty()){
                        int val1 = numbers.top();
                        numbers.pop();

                        char op = ops.top();
                        ops.pop();

                        numbers.push(applyOp(val1, val2, op));
                    }
                }
            }
            ops.push(tokens[i]); // Push the current operator onto the stack
        }
    }

// Apply remaining operations in the ops stack
    while(!ops.empty()){
        if(ops.top() == '~'){ // Direct application of unary operators at the end
            int val = numbers.top();
            numbers.pop();

            char op = ops.top();
            ops.pop();

            numbers.push(applyUnaryOp(val, op));
        } else if(numbers.size() >= 2){ // Ensure there are at least two operands for binary operations
            int val2 = numbers.top();
            numbers.pop();

            int val1 = numbers.top();
            numbers.pop();

            char op = ops.top();
            ops.pop();

            numbers.push(applyOp(val1, val2, op));
        }
    }

    return numbers.top();
}


int find_usedGates_Index(circuit &c,string comp_Name)
{
    int index = 0;

    for(auto gate : c.getusedGates())
    {

        if(gate.getCirCompName() == comp_Name)
        {
            return index;
        }
        else
        {
            index++;
        }

    }

    return -1;
}



int get_TimeStamp(shared_ptr<Logic_Gate> gate, int current_Time)
{

    int delay_ps = 0;

    delay_ps = gate->getDelayPs() + current_Time;

    return delay_ps;

}



