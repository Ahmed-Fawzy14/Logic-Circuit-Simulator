//
// Created by Fawzy on 3/11/2024.
//

#include "circuit.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Logic_Gate.cpp"
#include "TempMain.cpp"
using namespace std;

void readfile(ifstream &inputfile)
{
    string line1;

    // skip to COMPONENTS
    while (getline(cin, line1)) // loop used to reach the components
    {
        if (line1 == "COMPONENTS")
        {
            break;
        }
    }
}

void fillvector(vector<vector<string>> &components, ifstream &inputfile)
{
    string line2;

    while (getline(inputfile, line2))
    {

        istringstream iss(line2);         // istringstream used to split the line into tokens
        vector<string> component_details; // vector that will be used to push the tokens
        string token;
        while (iss >> token)
        {
            component_details.push_back(token); // tokens are read one by one and pushed into the vector
        }
        components.push_back(component_details); // the final component_details vector is pushed into components vector
    }
}

void objectmodification(vector<vector<string>> &components)
{
    // circuit localcircuit;
    // vector<Logic_Gate> usedgates;
    // traverse allgates and if name==name fill the object then push in usedgates
    for (int j = 0; j < components.size(); j++)
    {
        Library_Gate g1 = librarygates[components[i][1]]; // access the object in the map using the string name and add the attributes to g1
        {
            for (int j = 3; j < components[i].size(); j++)
            {
                g1.set_cir_Input_Names(components[i][j], -1) // adding the inputs to the object from the vector
            }
            g1.setCirOutput(components[i][2]);   // assign output to gate object
            g1.setCirCompName(components[i][1]); // assign special name
            usedgates.push_back(g1);             // push to usedgates vector
        }
    }
}


 bool circuit::Operator(int index,  vector<pair<string,int>> cir_Input_Names)
    {
        Logic_Gate gate = usedGates[index];

        vector<string> exp = gate.getExpression();

        //maps the value to its input var
        unordered_map<string, pair<string,int>> map;

        int i =0;
        for(auto x : exp)
        {
            if(i%2 == 0)
            {
                map[x] = cir_Input_Names[i];
                i++;
            }
            else
            {

                if(x == "&")
                    map[x] = make_pair("&", -2);
                //add the rest of the operators
            }

        }

        int j =0;
        bool output = 0;
        for(int j = 0; j<map.size(); j++)
        {
            string i1 = exp[j];
            string i2{};

            if(j%2 != 0)
            {
                if((map[i1].second).first == "&")
                    output = output & ((map[i1].second).second & (map[i1].second).second);
            }
        }


        return output;
    }



  
