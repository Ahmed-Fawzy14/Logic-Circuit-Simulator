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

string trimSpaces(const string& str) {
    string trimmed = str;
    // Remove spaces from both ends
    trimmed.erase(remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());
    return trimmed;
}

void circuit :: readLibFile(const string& filepath,  const string &fileName) // function to read lib file
{
    // declaring an input stream and string variables
    ifstream input;
    string line, name, no_of_inputs, delay, expression = {};

    // Opening the libfile
    input.open(filepath);

    // Creating an unordered map of the gates in the lib file
    map<string, Logic_Gate> librarygates;
    cout << input.is_open() << endl;
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

        librarygates[name] = gate; // adding the Logic_Gate object in the map of logic gates
    }
    input.close(); // closing the lib file

    ifstream cirfile(fileName);
    string line2("");
    while (getline(cirfile, line2) && line2 != "COMPONENTS:")
    {
        if (line2 == "INPUTS:")
            continue;
        else
        {
            trimSpaces(line2);
            cir_Inputs.push_back(line2);
        }
    }
    cirfile.close();
    setAllGates(librarygates);

    vector<vector<string>> components;

    fillVector(components, fileName);


}



void circuit::readStimFile(const string& filepath) {
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
    setCirInputs(inputs); // Assuming setcirInputs is a method to process or store the inputs

}



void circuit::fillVector(vector<vector<string>> &components, const string &fileName) {
    string line2;

    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return; // Early return if file cannot be opened
    }

    bool foundComponents = false; // Flag to indicate the "COMPONENTS:" line has been found

    while (getline(file, line2)) // Read each line from the file
    {
        // Check if we've found the "COMPONENTS:" line yet
        if (!foundComponents) {
            if (line2 == "COMPONENTS:") {
                foundComponents = true; // Set flag to true and skip processing this line
                continue;
            } else {
                continue; // Skip all lines until "COMPONENTS:" is found
            }
        }

        istringstream iss(line2); // Use istringstream to process the line
        vector<string> component_details; // Vector to hold the tokens
        string token;

        // Read tokens from the string until a comma is found
        while (getline(iss, token, ',')) // Use comma as delimiter
        {
            string trimmedToken = trimSpaces(token); // Assume this is a function to trim spaces from the token
            if (!trimmedToken.empty()) {
                component_details.push_back(trimmedToken); // Add the trimmed token to the vector
            }
        }

        components.push_back(component_details); // Add the component details to the components vector
    }

    objectModification(components); // Assume this is a function you've defined elsewhere
}


bool circuit::isOutputOfPreviousGate(std::string output, vector<Logic_Gate> &previousGates) {
    for (const auto &gate : previousGates)
    {
        if (gate.getCirOutputName() == output)
        {
            return true;
        }
    }
    return false;
}
void circuit ::objectModification(vector<vector<string>> &components)
{

    auto p = getAllGates();

    for (int i = 0; i < components.size(); i++)
    {

        if (components[i][0].empty() || components[i][1].empty() || components[i][2].empty())
            continue; // Skip this iteration if any of these critical fields are empty

        Logic_Gate g1;
        if (p.count(components[i][1]))
        {
            auto l = p.find(components[i][1]);
            g1 = l->second;
            for (int j = 3; j < components[i].size(); j++)
            {
                g1.setCirInputName(components[i][j], 0); // adding the inputs to the object from the vector
            }
            g1.setCirCompName(components[i][0]);

            g1.setCirOutputName(components[i][2]);
            pushGateInUsedGates(g1); // push to usedgates vector
        }
    }
    unordered_set<string> Set_of_inputs(cir_Inputs.begin(),cir_Inputs.end());
    for (const auto &gate : usedGates)
    {

        for (auto input : gate.get_cir_Input_Names())
        {

            if (Set_of_inputs.find(input.first) == Set_of_inputs.end() && !isOutputOfPreviousGate(input.first, usedGates))
            {
                cerr << "One of the inputs of the gates is invalid" << endl;
                exit(1);
            }
        }
    }
}



int circuit::usedGatessize() const {
    return usedGates.size();
}

void circuit::updateUsedGatesPtr() {
    usedGatesPtr.clear();
    for (auto& gate : usedGates) {
        usedGatesPtr.push_back(make_shared<Logic_Gate>(gate));
    }
}

vector<shared_ptr<Logic_Gate>>& circuit::getUsedGatesPtr() {
    return usedGatesPtr;
}

void circuit::setAllGates(const map<string, Logic_Gate>& Library_gates) {
    allGates = Library_gates;
}

const map<string, Logic_Gate>& circuit::getAllGates() const {
    return allGates;
}


vector<tuple<string, bool, int>>& circuit::getCirInputsRef() {
    return this->cirInputs;
}

void circuit::setUsedGates(const vector<Logic_Gate>& gates) {
    usedGates = gates;
}

void circuit::pushGateInUsedGates(const Logic_Gate& gate) {
    usedGates.push_back(gate);
}

void circuit::setCirInputs(const vector<tuple<string, bool, int>>& inputs) {
    cirInputs = inputs;
}

vector<Logic_Gate> circuit::getUsedGates() const {
    return usedGates;
}

vector<Logic_Gate>& circuit::getRefUsedGates() {
    return this->usedGates;
}

vector<tuple<string, bool, int>> circuit::getCirInputs() const {
    return cirInputs;
}


void circuit::sortCirInputs() {
    auto& inputs = getCirInputsRef();
    sort(inputs.begin(), inputs.end(),
         [](const tuple<string, bool, int> &a, const tuple<string, bool, int> &b) {
             return get<2>(a) < get<2>(b);
         });
}




