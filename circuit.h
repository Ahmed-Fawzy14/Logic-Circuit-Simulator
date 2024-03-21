//
// Created by Fawzy on 3/11/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#include "Logic_Gate.h"
#include <unordered_map>
#include <queue>

class circuit {
private:

    //This has all the circuit components
    //Traverse over allGates to fill this
    //Use the vector for flagging method 
    vector<Logic_Gate> usedGates;
    //Use the Queue for popping method 
   // queue<Logic_Gate> usedGates;

    //This is the worst case propogation delay in ps
    int propgration_Delay_ps;

    //This is the final time in the .stim file
    int time_End;

     vector<tuple<string, bool, int>> cirInputs;
    unordered_map<string, tuple <string, bool, int>> current_Inputs_Map;


public:



    void Run();

    //Send the index of the object in usedGates to this function and the current cir_Input_Names
    //bool Operator(int index, vector<tuple <string, bool, int>> current_Inputs);

    void setcurrent_Inputs_Map( unordered_map<string, tuple <string, bool, int>> current_Inputs_Map)
    {
        this->current_Inputs_Map = current_Inputs_Map;
    }

    unordered_map<string, tuple <string, bool, int>> getcurrent_Inputs_Map()
    {
        return current_Inputs_Map;
    }

    unordered_map<string, tuple <string, bool, int>>& getcurrent_Inputs_MapREF()
    {
        return this-> current_Inputs_Map;
    }

    void setusedGates(vector <Logic_Gate> gates)
    {
        usedGates = gates;
    }

    void setcirInputs(vector<tuple<string, bool, int>> inputs)
    {
        cirInputs = inputs;
    }

    vector <Logic_Gate> getusedGates()
    {
       return usedGates;
    }

    vector <Logic_Gate>& getREF_usedGates()
    {
        return this->usedGates;
    }

    vector <tuple<string, bool, int>> getcirInputs()
    {
        return cirInputs;
    }

    
    void objectmodification(vector<vector<string>> &components);
    void readfile(ifstream &inputfile);
    void fillvector(vector<vector<string>> &components, ifstream &inputfile);
};


#endif //LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
