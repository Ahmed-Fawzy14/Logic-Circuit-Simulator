//
// Created by Fawzy on 3/16/2024.
//
#include "testOperator.h"
#include <stack>
#include <vector>
#include <string>
#include <utility>
#include <sstream>

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


int evaluate(circuit &c, int usedGates_Index){
    string tokens = (c.getusedGates())[usedGates_Index].getExpression();
    vector<pair<string,int>> sample_cir_Input_Names = (c.getusedGates())[usedGates_Index].get_cir_Input_Names();

    //issue is that we need a string with the values of the expression not i1,i2
    //the solution is that the algorithm already splits the operators from the letters so all we need to do is assign the
    //first element found in tokens as the first element in sample_cir_Input_Names
    //So in stim file the input entered first is i1 then the second inputs is i2 and so on

    stack<int> values;
    stack<char> ops;
    int expression_Index = 0;
    int checkNumOfInputs = 0;
    string currentInputName; // To accumulate non-operator characters

    for(int j = 0; j < tokens.length(); j++) {
        char currentChar = tokens[j];
        bool isOperator = currentChar == '&' || currentChar == '|' || currentChar == '~';

        // Check if the character is an operator or a space
        if (isOperator || currentChar == ' ') {
            // Process the accumulated input name (if any) before handling the operator
            if (!currentInputName.empty()) {
                // Here, determine the value based on 'currentInputName'
                int value;
                if (currentInputName == "1") {
                    value = 1;
                } else if (currentInputName == "0") {
                    value = 0;
                } else {
                    // Map the accumulated name to its value based on the order it appears in 'sample_cir_Input_Names'
                    value = sample_cir_Input_Names[expression_Index].second;
                }

                // Optionally, modify 'tokens' or perform other actions with 'value'
                // For illustration: replace the name in tokens with its value (as a char)
                // This is a simplification and might need adjustment to fit your logic
                // Note: This direct replacement might not work for multi-character names/values and is for illustration only
                tokens.replace(j - currentInputName.length(), currentInputName.length(), std::to_string(value));

                checkNumOfInputs++;
                expression_Index++;
                currentInputName.clear(); // Reset for the next input name
            }
            // Directly handle operators here if necessary
        } else {
            // Accumulate non-operator characters into the current input name
            currentInputName += currentChar;
        }
    }

// Check and process any remaining input name after the loop
    if (!currentInputName.empty()) {
        // Similar logic to map 'currentInputName' to its value and take action
        int value = sample_cir_Input_Names[expression_Index].second;
        checkNumOfInputs++;
        // Direct replacement for illustration; adjust as necessary
        tokens.replace(tokens.length() - currentInputName.length(), currentInputName.length(), std::to_string(value));
        expression_Index++;
    }

    /*for(int j=0; j<tokens.length(); j++)
    {
        if((tokens[j] >= 97 && tokens[j] <=122) || (tokens[j] == 49) || (tokens[j] == 48) )
        {

            if((tokens[j] == 49))
            {
                int value = 1;
                checkNumOfInputs++;
                if(value == 0  || value == 1)
                    tokens[j] = value + '0';
                expression_Index++;
            }
            else if((tokens[j] == 48))
            {
                int value = 0;
                checkNumOfInputs++;
                if(value == 0  || value == 1)
                    tokens[j] = value + '0';
                expression_Index++;
            }
            else
            {
                int value = sample_cir_Input_Names[expression_Index].second;
                checkNumOfInputs++;
                if(value == 0  || value == 1)
                    tokens[j] = value + '0';
                expression_Index++;
            }



        }
    }*/

    if(checkNumOfInputs != (c.getusedGates())[usedGates_Index].getNumOfInputs())
    {
        cout<<"Invalid inputs number for component: "<<(c.getusedGates())[usedGates_Index].getCirOutputName()<<endl;
        return -1;
    }


    for(int i = 0; i < tokens.length(); ++i){
        if(tokens[i] == ' ') continue;
        // If token is a number

        if(isdigit(tokens[i])){
            int val = 0;
            while(i < tokens.length() && isdigit(tokens[i])){
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            values.push(val);
            i--; // Since the for loop also increments i
        }
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
        else if(tokens[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
                int val2 = values.top();
                values.pop();

                if(ops.top() != '~'){
                    int val1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    values.push(applyOp(val1, val2, op));
                }
            }

            // Pop the opening '('
            if(!ops.empty()) ops.pop();
        }
        else if(tokens[i] == '~'){
            // Check for consecutive '~' operators
            int count = 0;
            while(i < tokens.length() && tokens[i] == '~'){
                ++count;
                ++i;
            }
            --i; // Adjust because the for loop will increment i

            // If an odd number of '~', it's effectively one '~' operation
            if(count % 2 == 1){
                if(!values.empty()){
                    int val = values.top();
                    values.pop();
                    values.push(applyUnaryOp(val, '~'));
                } else {
                    // Handle case where '~' is before any number or expression
                    ops.push('~');
                }
            }
            // Even number of '~' cancel out, no operation needed
        }
        else {
            while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])){
                int val2 = values.top();
                values.pop();

                // Handle unary operator separately
                if(ops.top() == '~'){
                    values.push(applyUnaryOp(val2, ops.top()));
                } else {
                    int val1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    values.push(applyOp(val1, val2, op));
                }
            }

            // For non-unary operators
            if(tokens[i] != '~') ops.push(tokens[i]);
        }
    }

    // Final evaluation of remaining operations
    while(!ops.empty()){
        int val2 = values.top();
        values.pop();

        if(ops.top() == '~'){
            values.push(applyUnaryOp(val2, ops.top()));
            ops.pop();
        } else if(!values.empty()){
            int val1 = values.top();
            values.pop();

            char op = ops.top();
            ops.pop();

            values.push(applyOp(val1, val2, op));
        }
    }

    return values.top();
}

void input_exisits(circuit &c, unordered_map<string, tuple <string, bool, int>> &current_Inputs_Map,  unordered_map<string, bool> &flag)
{

    unordered_map<string, tuple <string, bool, int>>::iterator search;


    for(auto &gate : c.getREF_usedGates())
    {
        for(auto &inputs : gate.getREF_cir_Input_Names())
        {
            flag[gate.getCirCompName()] = current_Inputs_Map.count(inputs.first);

            if(flag[gate.getCirCompName()] == 1)
            {

                search = current_Inputs_Map.find(inputs.first);
                inputs.second = get<1>(search->second);


            }
        }

    }

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



/*int evaluate_Expression(circuit &c, int usedGates_Index) {

    vector<string> expression = (c.getusedGates())[usedGates_Index].getExpression();
    vector<pair<string,int>> sample_cir_Input_Names = (c.getusedGates())[usedGates_Index].get_cir_Input_Names();

    int element_Index = 0;
    int output = sample_cir_Input_Names.size() > 0 ? sample_cir_Input_Names[0].second : 0;


    //Increments by 2 to skip to operators
    for (int i = 1; i < expression.size(); i += 2) {
        //Check pair exists
        if (i + 1 < expression.size()) {
            //Store the operator we need to use
            string operation = expression[i];
            //
            int nextInputValue = sample_cir_Input_Names[i / 2 + 1].second;

            if (operation == "&") {
                output &= nextInputValue;
            } else if (operation == "|") {
                output |= nextInputValue;
            }
        }
    }


    return output;

}*/

int get_TimeStamp(circuit &sample_c, int current_Time, int usedGates_Index )
{

    int delay_ps = 0;

    Logic_Gate gate = (sample_c.getusedGates())[usedGates_Index];
    delay_ps = gate.getDelayPs() + current_Time;

    return delay_ps;

}


int run_Operator_Test(circuit &c, int current_Time, int &isNotReady)
{
    isNotReady = 0;
    //Is used to map the same of a circuit component to whether it is ready to be evaluated
    unordered_map<string, bool> flag;

    //initial run of input exists
    input_exisits(c, c.getcurrent_Inputs_MapREF(), flag);



    //Each output to be evaluated then pushed into current_Inputs_Map
    int output = 0;

    //Each time to be evaluated then pushed into current_Inputs_Map
    int new_Time = 0;

    //when this is equal to number of inputs in usedGates we know the next output to be pushed will be the final output of the cirucit to be used in the truth table
    int final_Output_Counter = 0;
    unordered_map<string, int> final_Outputs;
    //need to receive this
    int currentTime = 100;
    for(auto &element : flag)
    {
        int usedGates_Index = find_usedGates_Index(c,element.first);
        Logic_Gate current_Gate = c.getusedGates()[usedGates_Index];
        string current_comp_name = (c.getusedGates())[usedGates_Index].getCirOutputName();
        auto current_cirInputNames = (current_Gate.get_cir_Input_Names());

        if(current_Gate.getNumOfInputs() != (current_cirInputNames).size())
        {
            cout<<"Invalid inputs number for component: "<<current_Gate.getCirCompName()<<endl;
        }

        //Updating run
        input_exisits(c, c.getcurrent_Inputs_MapREF(), flag);

        //If all inputs are present
        if(element.second == 1)
        {


            output = evaluate(c, usedGates_Index);

            if(output == -1)
            {
                cout<<"Invalid inputs number for component: "<<(c.getusedGates())[usedGates_Index].getCirOutputName()<<endl;
                return -1;
            }
            else
            {
                new_Time = get_TimeStamp(c, current_Time, usedGates_Index);
                final_Output_Counter++;
                //not sure how to do final output becase there may be more than one output
                if(final_Output_Counter == (c.getusedGates()).size())
                {
                    cout<<"Final Output for "<<element.first<<"is: "<<output<<" at time "<<new_Time<<endl;
                    final_Outputs[current_comp_name] = output;
                    (c.getcurrent_Inputs_MapREF())[current_comp_name] = make_tuple(current_comp_name, output, new_Time);

                }
                else
                {
                    cout<<"Output for "<<element.first<<"is: "<<output<<" at time "<<new_Time<<endl;
                    (c.getcurrent_Inputs_MapREF())[current_comp_name] = make_tuple(current_comp_name, output, new_Time);

                }
            }

        }
        else
        {
            cout<<"Component "<<element.first<< " not ready"<<endl;
            isNotReady++;
        }
    }


    return 0;

}
