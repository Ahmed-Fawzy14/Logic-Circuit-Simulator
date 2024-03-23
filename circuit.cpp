//
// Created by Fawzy on 3/11/2024.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Logic_gate.h"
#include <map>
#include "circuit.h"
using namespace std;


void circuit :: read_lib_file(const string& filepath, string fileName) // function to read lib file
{
// declaring an input stream and string variables
    ifstream input;
    string line, name, no_of_inputs, delay, expression = {};

    // Opening the libfile
    input.open(filepath);

// Creating an unordered map of the gates in the lib file
    map<string, Logic_Gate> librarygates;
    cout<<input.is_open()<<endl;
// A while loop to go through all the data in the lib file
    while (getline(input, line))
    {
        // Creating an istringstream object and initializing it with a string (line)
        istringstream subst(line);

        // Reading data from the lib file and storing each string in its respective variable
        getline(subst, name, ',');
        getline(subst, no_of_inputs, ',');
        getline(subst, expression, ',');
        getline(subst, delay, ',');

        // Looping over the string expression and storing each character in it in a seperate vector

        auto inputs = stoi(no_of_inputs);
        auto de = stoi(delay);




        // Constructing a Logic_Gate object and initializing its variables with the data from the lib file
        Logic_Gate gate(name, inputs, de, expression);
        librarygates[name] = gate;


        librarygates[name] = gate; //adding the Logic_Gate object in the map of logic gates
    }
    input.close(); // closing the lib file


    set_All_gates(librarygates);

    vector<vector<string>> components;

    fillvector(components,fileName);

}

string trimSpaces(const string& str) {
    string trimmed = str;
    // Remove spaces from both ends
    trimmed.erase(remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());
    return trimmed;
}
void circuit::read_stim_file(const string& filepath) {
    string line, Input, value, timestamp;
    ifstream input(filepath.c_str());
    vector<tuple<string, bool, int>> inputs;

    while (getline(input, line)) {
        istringstream subst(line);

        // Read data from each line
        getline(subst, timestamp, ',');
        getline(subst, Input, ',');
        getline(subst, value, ',');

        // Trim spaces from the strings
        timestamp = trimSpaces(timestamp);
        Input = trimSpaces(Input);
        value = trimSpaces(value);

        // Converting value and timestamp to integers to be passed on to the make_tuple function
        int int_Value = stoi(value);
        int int_Timestamp = stoi(timestamp);

        // Create a tuple and insert it into the inputs vector
        inputs.push_back(make_tuple(Input, static_cast<bool>(int_Value), int_Timestamp));
    }

    input.close(); // Closing the stim file
    setcirInputs(inputs); // Assuming setcirInputs is a method to process or store the inputs

}

void circuit::write_to_sim(string fileName){
    ofstream output; // Declaring an ofstream object to write the output into the file

    // Opening the file in default mode to clear it and then write new content
    output.open(fileName);

    if (!output.is_open()) {
        cerr << "There was an error opening the file.";
        return; // Early return if file can't be opened
    }

    // A loop to write the output in the format of a sim file (timestamp, input_name, value)
    for (const auto& element : cirInputs) {
        output << get<2>(element) << " " << get<0>(element) << " " << get<1>(element) << "\n";
        cout << get<2>(element) << " " << get<0>(element) << " " << get<1>(element) << "\n";
    }

    output.close(); // Closing the file after writing all elements
}




void circuit::fillvector(vector<vector<string>> &components, string fileName) {
    string line2;

    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return; // Early return if file cannot be opened
    }

    while (getline(file, line2)) // Read each line from the file
    {
        istringstream iss(line2); // Use istringstream to process the line
        vector<string> component_details; // Vector to hold the tokens
        string token;

        // Read tokens from the string until a comma is found
        while (getline(iss, token, ',')) // Use comma as delimiter
        {
            string trimmedToken = trimSpaces(token); // Trim spaces from the token
            if (!trimmedToken.empty()) {
                component_details.push_back(trimmedToken); // Add the trimmed token to the vector
            }
        }

        components.push_back(component_details); // Add the component details to the components vector
    }

    objectmodification(components); // Assume this is a function you've defined elsewhere
}

void circuit :: objectmodification(vector<vector<string>> &components)
{

    auto p = get_All_gates();

    for (int i = 5; i < components.size(); i++)
    {

        if(components[i][0].empty() || components[i][1].empty() || components[i][2].empty())
            continue; // Skip this iteration if any of these critical fields are empty

        Logic_Gate g1;
        if(p.count(components[i][1]))
        {
            auto l = p.find(components[i][1]);
            g1 = l->second;
            for (int j = 3; j < components[i].size(); j++)
                {
                   g1.setCirInputName(components[i][j], -1); // adding the inputs to the object from the vector
                }
            g1.setCirCompName(components[i][0]);

            g1.setCirOutputName(components[i][2]);
            pushgate_in_usedGates(g1);             // push to usedgates vector

        }

    }

}





void circuit::sort_Cir_inputs() {
    auto& inputs = getcirInputsREF(); // Ensure getCirInputs() returns a reference
    sort(inputs.begin(), inputs.end(),
         [](const tuple<string, bool, int> &a, const tuple<string, bool, int> &b) {
             return get<2>(a) < get<2>(b);
         });
}




