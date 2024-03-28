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

<<<<<<< Updated upstream
//start of inserting values into expression
// this function returns the prefix of the operand in the expression in case it is not "i"
string getoperand(const string &expression)
{
    for (int i = 0; i < expression.size(); i++)
    { // loops through all expressions looking for operands
        if (isdigit(expression[i]))
        { // digit found
            int prefixend = i;
            if (prefixend == 0)
                continue; // makes sure code doesnt leave string
            int prefixstart = i - 1;
            while (prefixstart > 0 && isalpha(expression[prefixstart - 1]))
            {

                prefixstart--;
            }
            return expression.substr(prefixstart, prefixend);
        }
    }
    return " ";
}

string insertValuesInExpression(Logic_Gate gate1)
{
    // 1 & 0
    // A(1), B(0)

    // i1 & i2
    // A, B, C

    // substitue in the expression each operand with the value of the input

    // check that cirinputnames(in cir file)== gate.noinputs(lib)

    string expression = gate1.getExpression(); // extract expression
    string prefix = getoperand(expression);
    cout << prefix;
    if (prefix.empty())
    {
        cout << "No operand prefix detected." << endl;
        return expression; // return the original expression if no prefix is detected
    }
=======
void insertValuesInExpression(string &exp, vector<pair<string,int>> &sample_cir_Input_Names) {

    //1 & 0
    //A(1), B(0)

    //check that cirinput names== gate.noinputs


    //i1 & i2
    //A, B, C


>>>>>>> Stashed changes

    vector<pair<string, int>> inputs = gate1.get_cir_Input_Names(); // extract cirinputnames
    // vector<pair<string, int>> inputs = sample_cir_Input_Names;

    int expectedinputs = gate1.getNumOfInputs();
    if (inputs.size() != expectedinputs) // makes sure the number of inputs and the size of vector are equal
    {
        cout << "number of inputs is not same as expected " << endl;
        return "";
    }
    else
    {
        for (int i = 0; i < inputs.size(); ++i)
        {
            string operandexpression = prefix + to_string(i + 1); // make a variable with the operand in the expression
            size_t position = expression.find(operandexpression); // find first instance of the operand in expression
            while (position != string::npos)
            {
                expression.replace(position, operandexpression.length(), to_string(inputs[i].second)); // replaces instance of operandexpression with value of input in cirinputs
                position = expression.find(operandexpression, position + 1);
            }
        }
        return expression;
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
       // cout<<"Invalid inputs number for component: "<<(c.getusedGates())[usedGates_Index].getCirOutputName()<<endl;
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
        bool allInputsPresent = true;
        std::string inputSequence;

        // Construct the input sequence string
        for (auto &input : gate.getREF_cir_Input_Names()) {
            auto search = c.getcurrent_Inputs_MapREF().find(input.first);
            if (search != c.getcurrent_Inputs_MapREF().end()) {
                input.second = std::get<1>(search->second); // Update input value
                inputSequence += std::to_string(input.second) + ",";
            } else {
                allInputsPresent = false; // Not all inputs are present
                break;
            }
        }

        if (allInputsPresent) {
            // Compute hash of the input sequence
            std::hash<std::string> hasher;
            std::size_t sequenceHash = hasher(inputSequence);

            // Check if the hash exists in the gate's previousInputHashes
            if (gate.previousInputHashes.find(sequenceHash) == gate.previousInputHashes.end()) {
                // It's a new sequence, so process accordingly and add hash to set
                gate.previousInputHashes.insert(sequenceHash);
                flag[gate.getCirCompName()] = std::make_pair(true, true); // Ready for processing
            } else {
                // Sequence has been seen before, not ready for processing
<<<<<<< Updated upstream
                flag[gate.getCirCompName()] = std::make_pair(true, false);
=======
              //  flag[gate.getCirCompName()] = std::make_pair(true, false);
>>>>>>> Stashed changes
            }
        } else {
            // If not all inputs are present, indicate that the gate is not ready for processing
            flag[gate.getCirCompName()] = std::make_pair(false, false);
        }
    }

    index++; // Increment index for tracking purposes
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
        }


        //If all inputs are present
        if((element.second).second == 1)
        {


            output = evaluate(c, usedGates_Index);

            if(output == -1)
<<<<<<< Updated upstream
            {
=======
            {           cout<<"Invalid inputs number for component: "<<current_Gate.getCirCompName()<<endl;

>>>>>>> Stashed changes
                return -1;
            }
            else if(output == 0 || output ==  1)
            {
                new_Time = get_TimeStamp(c, current_Time, usedGates_Index);
                (c.getcirInputsREF()).push_back(make_tuple(current_comp_name, output, new_Time));
            }

        }
        else
        {
            //Component is not ready
        }
    }

    return 0;

}
