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

void insertValuesInExpression(string &tokens, vector<pair<string,int>> &sample_cir_Input_Names, int &checkNumOfInputs) {
    int expression_Index = 0;
    string currentInputName;

    for (int j = 0; j < tokens.length(); ++j) {
        char currentChar = tokens[j];
        bool isOperator = currentChar == '&' || currentChar == '|' || currentChar == '~';
        bool isParenthesis = currentChar == '(' || currentChar == ')'; // Check for parentheses

        if (isOperator || currentChar == ' ' || isParenthesis) { // Treat parentheses as special cases
            if (!currentInputName.empty()) {
                // Replace the currentInputName with its corresponding value
                int value = (currentInputName == "1") ? 1 : (currentInputName == "0") ? 0 : sample_cir_Input_Names[expression_Index].second;
                tokens.replace(j - currentInputName.length(), currentInputName.length(), std::to_string(value));
                j -= currentInputName.length() - 1; // Adjust 'j' based on the length difference

                checkNumOfInputs++;
                expression_Index++;
                currentInputName.clear(); // Reset for the next input name
            }
            if (isParenthesis) {
                // Do not clear currentInputName if the current character is a parenthesis
                continue; // Move to the next character without altering the loop variable or currentInputName
            }
        } else {
            // Accumulate non-operator characters into the current input name
            currentInputName += currentChar;
        }
    }

    // Handle the last accumulated input name if not empty
    if (!currentInputName.empty()) {
        int value = (currentInputName == "1") ? 1 : (currentInputName == "0") ? 0 : sample_cir_Input_Names[expression_Index].second;
        tokens.replace(tokens.length() - currentInputName.length(), currentInputName.length(), std::to_string(value));

        checkNumOfInputs++;
        expression_Index++;
    }


}

int evaluate(circuit &c, int usedGates_Index){


    string tokens = (c.getusedGates())[usedGates_Index].getExpression();
    vector<pair<string,int>> sample_cir_Input_Names = (c.getusedGates())[usedGates_Index].get_cir_Input_Names();

    stack<int> numbers;
    //operators
    stack<char> ops;
    int checkNumOfInputs = 0;

    insertValuesInExpression(tokens, sample_cir_Input_Names, checkNumOfInputs);


    if(checkNumOfInputs != (c.getusedGates())[usedGates_Index].getNumOfInputs())
    {
        cout<<"Invalid inputs number for component: "<<(c.getusedGates())[usedGates_Index].getCirOutputName()<<endl;
        return -1;
    }


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


void input_exists_hashed(circuit &c, unordered_map<string, pair<bool, bool>> &flag, int &index) {
    for (auto &gate : c.getREF_usedGates()) {
        cout << "Processing gate: " << gate.getCirCompName() << endl;
        bool allInputsPresent = true;
        std::string inputSequence;

        // Construct the input sequence string
        for (auto &input : gate.getREF_cir_Input_Names()) {
            auto search = c.getcurrent_Inputs_MapREF().find(input.first);
            if (search != c.getcurrent_Inputs_MapREF().end()) {
                input.second = std::get<1>(search->second); // Update input value
                inputSequence += std::to_string(input.second) + ",";
                cout << "Input " << input.first << " found with value " << input.second << endl;
            } else {
                allInputsPresent = false; // Not all inputs are present
                cout << "Input " << input.first << " not found" << endl;
                break;
            }
        }

        if (allInputsPresent) {
            cout << "All inputs present for " << gate.getCirCompName() << endl;
            // Compute hash of the input sequence
            std::hash<std::string> hasher;
            std::size_t sequenceHash = hasher(inputSequence);

            // Check if the hash exists in the gate's previousInputHashes
            if (gate.previousInputHashes.find(sequenceHash) == gate.previousInputHashes.end()) {
                // It's a new sequence, so process accordingly and add hash to set
                gate.previousInputHashes.insert(sequenceHash);
                flag[gate.getCirCompName()] = std::make_pair(true, true); // Ready for processing
                cout << "New input sequence for " << gate.getCirCompName() << "; processing." << endl;
            } else {
                // Sequence has been seen before, not ready for processing
                flag[gate.getCirCompName()] = std::make_pair(true, false);
                cout << "Input sequence for " << gate.getCirCompName() << " has been seen before; skipping." << endl;
            }
        } else {
            // If not all inputs are present, indicate that the gate is not ready for processing
            flag[gate.getCirCompName()] = std::make_pair(false, false);
            cout << "Not all inputs present for " << gate.getCirCompName() << "; not ready for processing." << endl;
        }
    }

    index++; // Increment index for tracking purposes
    cout << "Incrementing index to: " << index << endl;
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



int get_TimeStamp(circuit &sample_c, int current_Time, int usedGates_Index )
{

    int delay_ps = 0;

    Logic_Gate gate = (sample_c.getusedGates())[usedGates_Index];
    delay_ps = gate.getDelayPs() + current_Time-1;

    return delay_ps;

}

bool checkVector(vector <tuple<string, bool, int>> cirInputs, tuple<string, bool, int> tup)
{
    for(auto x: cirInputs)
    {
        if(x == tup)
            return 0;

    }

    return 1;
};

int run_Operator_Test(circuit &c, int current_Time, unordered_map<string, tuple <string, bool, int>> &current_Outputs_Map, int &prevInpIndex)
{

    //Is used to map the same of a circuit component to whether it is ready to be evaluated
    //first bool for each input, second bool for all inputs
    unordered_map<string, pair<bool,bool>> flag;
    //initial run of input exists
    input_exists_hashed(c,  flag, prevInpIndex);


    //Each output to be evaluated then pushed into current_Inputs_Map
    int output = -2;

    //Each time to be evaluated then pushed into current_Inputs_Map
    int new_Time = 0;

    unordered_map<string, int> final_Outputs;

    for(auto &element : flag)
    {
        int usedGates_Index = find_usedGates_Index(c,element.first);
        Logic_Gate current_Gate = c.getusedGates()[usedGates_Index];
        string current_comp_name = (c.getusedGates())[usedGates_Index].getCirOutputName();
        auto current_cirInputNames = (current_Gate.get_cir_Input_Names());
        auto current_Output_Name = c.getusedGates()[usedGates_Index].getCirOutputName();

        if(current_Gate.getNumOfInputs() != (current_cirInputNames).size())
        {
            cout<<"Invalid inputs number for component: "<<current_Gate.getCirCompName()<<endl;
        }


        //If all inputs are present
        if((element.second).second == 1)
        {


            output = evaluate(c, usedGates_Index);
            cout<<output<<endl;

            if(output == -1)
            {
                cout<<"Invalid inputs number for component!!!!: "<<(c.getusedGates())[usedGates_Index].getCirOutputName()<<endl;
                return -1;
            }
            else if(output == 0 || output ==  1)
            {
                new_Time = get_TimeStamp(c, current_Time, usedGates_Index);
                (c.getcirInputsREF()).push_back(make_tuple(current_comp_name, output, new_Time));
                cout<<"pushing into cirinputs: "<<current_comp_name<<'\t'<<output<<'\t'<<new_Time<<endl;
            }

        }
        else
        {
            cout<<"Component "<<element.first<< " not ready"<<endl;
        }
    }

    return 0;

}
