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
#include <iostream>
#include <regex>


using namespace std;

//This function decides the precedence of operators based on boolean algebra
int precedence(char op){
    if (op == '~') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0;
}

//This function applied the operation after the inputs have been correctly placed
int applyOp(int a, int b, char op){
    switch(op){
        case '&': return a & b;
        case '|': return a | b;
        default: return 0;
    }
}

//This function applied the operation after the input have been correctly placed for the NOT operator since it in Unary
int applyUnaryOp(int a, char op){
    // Directly handling '~' as logical NOT for 0 and 1
    if(op == '~'){
        //If a is 0 the output is 1 else output is 0
        return a == 0 ? 1 : 0;
    }
    return 0;
}

string replaceOperands(shared_ptr<Logic_Gate> gate, bool &samevalue)
{
    string updatedExpression = gate->getExpression(); // receive the expression of the gate
    auto inputs = gate->get_cir_Input_Names();        // receive cir_input_names
    int expectedinputs = gate->getNumOfInputs();      // receive the variable NumofInputs

    if (inputs.size() != expectedinputs) // Error handling for incomplete inputs in .cir
    {
        cerr << "number of inputs is not same as expected " << endl;
        samevalue = false;
        exit(1);
        return "";
    }
    else
    {
        for (int i = 0; i < inputs.size(); ++i) // iterates input
        {

            string operand = "i" + to_string(i + 1);    // construct the operand ("i1", "i2", etc.)
            string value = to_string(inputs[i].second); // get input value

            regex pattern(operand + "(\\D|$)"); // regex to match placeholder

            updatedExpression = regex_replace(updatedExpression, pattern, value + "$1"); // updates the expression
        }
        return updatedExpression;
    }
}

//Application of the shunting yard algorithm
void shuntingYard(string &tokens, int &i, stack<int> &values,stack<char> &operators)
{

    // If token is a number
    if(isdigit(tokens[i])){
        int val = 0;
        while(i < tokens.length() && isdigit(tokens[i])){
            val = (val * 10) + (tokens[i] - '0');
            i++;
        }
        values.push(val);
        i--;
    }
    else if(tokens[i] == '('){
        operators.push(tokens[i]);
    }
    else if(tokens[i] == ')'){
        while(!operators.empty() && operators.top() != '('){
            int val2 = values.top();
            values.pop();

            if(operators.top() != '~'){
                int val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyOp(val1, val2, op));
            } else {
                // Direct application of unary operators before closing parenthesis
                char op = operators.top();
                operators.pop();

                values.push(applyUnaryOp(val2, op));
            }
        }
        // Pop the '(' operator
        if(!operators.empty()) operators.pop();
    }
    else if(tokens[i] == '~'){
        // Push '~' onto the operators stack to signify a pending unary operation
        operators.push(tokens[i]);
    }
    else {
        // When encountering a binary operator, check the precedence and apply operations accordingly
        while(!operators.empty() && precedence(operators.top()) >= precedence(tokens[i])){
            if(operators.top() == '~'){ // Handle unary operator '~' immediately
                int val = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyUnaryOp(val, op));
            } else { // Handle binary operators based on precedence
                int val2 = values.top();
                values.pop();

                if(!values.empty()){
                    int val1 = values.top();
                    values.pop();

                    char op = operators.top();
                    operators.pop();

                    values.push(applyOp(val1, val2, op));
                }
            }
        }
        operators.push(tokens[i]); // Push the current operator onto the stack
    }
}

//Final stage of shunting yard
void FinishShuntingYard(stack<int> &numbers,stack<char> &operators)
{
    if(operators.top() == '~'){ // Direct application of unary operators at the end
        int val = numbers.top();
        numbers.pop();

        char op = operators.top();
        operators.pop();

        numbers.push(applyUnaryOp(val, op));
    } else if(numbers.size() >= 2){ // Ensure there are at least two operands for binary operations
        int val2 = numbers.top();
        numbers.pop();

        int val1 = numbers.top();
        numbers.pop();

        char op = operators.top();
        operators.pop();

        numbers.push(applyOp(val1, val2, op));
    }

}

//Function makes necessary calls for evaluating the expression
bool evaluate(shared_ptr<Logic_Gate> g, int time){


    vector<pair<string,int>> cir_Input_Names = g->get_cir_Input_Names();
    bool samenumber = true;


    stack<int> values;
    //operators
    stack<char> operators;

    //This function inserts the values from cirInputNames into the expression of the current gate
    string tokens = replaceOperands(g, samenumber);


    for(int i = 0; i < tokens.length(); ++i)
    {
        if(tokens[i] == ' ') continue;

        shuntingYard(tokens, i, values, operators);
    }

// Apply remaining operations in the operators stack
    while(!operators.empty())
    {
        FinishShuntingYard(values,operators);
    }

    return values.top();
}


int find_usedGates_Index(circuit &c,string comp_Name)
{
    int index = 0;

    for(auto gate : c.getUsedGates())
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


//Calculates the correct time value that will be used for new outputs in the time stack
int get_TimeStamp(shared_ptr<Logic_Gate> gate, int current_Time)
{

    int delay_ps = 0;

    delay_ps = gate->getDelayPs() + current_Time;

    return delay_ps;

}



