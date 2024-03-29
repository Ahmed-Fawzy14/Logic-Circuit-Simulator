//
// Created by Fawzy on 3/11/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#include "Logic_Gate.h"
#include <map>
#include <queue>
#include <iostream>
using namespace std;

class circuit {
private:

    //This has all the circuit components
    //Traverse over allGates to fill this
    //Use the vector for flagging method
    vector<Logic_Gate> usedGates;

    vector<shared_ptr<Logic_Gate>> usedGatesPtr;

    //This is the worst case propogation delay in ps
    int propgration_Delay_ps;

    //This is the final time in the .stim file
    int time_End;

    vector <tuple<string, bool, int>> cirInputs;
    map <string, tuple <string, bool, int>> current_Inputs_Map;
    map <string, Logic_Gate>  All_gates;




public:



    void printLogicGateContents();



    int usedGatessize(){
        return usedGates.size();
    }

    void Run();

    //Send the index of the object in usedGates to this function and the current cir_Input_Names
    //bool Operator(int index, vector<tuple <string, bool, int>> current_Inputs);

    void updateUsedGatesPtr() {
        usedGatesPtr.clear(); // Clear existing shared pointers
        for (auto& gate : usedGates) {
            usedGatesPtr.push_back(make_shared<Logic_Gate>(gate));
        }
    }

    // Getter for usedGatesPtr
    vector<shared_ptr<Logic_Gate>>& getUsedGatesPtr() {
        return usedGatesPtr;
    }

    void set_All_gates(map <string, Logic_Gate> Library_gates)
    {
        All_gates = Library_gates;
    }

    map <string, Logic_Gate> get_All_gates()
    {
        return All_gates;
    }

    void setcurrent_Inputs_Map(map<string, tuple <string, bool, int>> current_Inputs_Map)
    {
        this->current_Inputs_Map = current_Inputs_Map;
    }

    map<string, tuple <string, bool, int>> getcurrent_Inputs_Map()
    {
        return current_Inputs_Map;
    }

    map<string, tuple <string, bool, int>>& getcurrent_Inputs_MapREF()
    {
        return this-> current_Inputs_Map;
    }


    vector< tuple <string, bool, int>>& getcirInputsREF()
    {
        return this-> cirInputs;
    }

    void setusedGates(vector <Logic_Gate> gates)
    {
        usedGates = gates;
    }

    void pushgate_in_usedGates(Logic_Gate gate){
        usedGates.push_back(gate);
    }

    void setcirInputs(vector <tuple <string, bool, int>>& inputs)
    {
        cirInputs = inputs;
    }
    void objectmodification(vector<vector<string>> &components);
    void fillvector(vector<vector<string>> &components, string fileName);

    vector <Logic_Gate> getusedGates()
    {
        return usedGates;
    }

    vector <Logic_Gate>& getREF_usedGates()
    {
        return this->usedGates;
    }

    vector< tuple <string, bool, int>> getcirInputs()
    {
        return cirInputs;
    }

    void read_lib_file(const string& filepath, string fileName); // function to read lib file
    void write_to_sim(string fileName);
    void read_stim_file(const string& filepath);

    //  void objectmodification(vector<vector<string>> &components);
    // void read_circ_file(ifstream &inputfile);
    // void fillvector(vector<vector<string>> &components,  ifstream &inputfile);
    void sort_Cir_inputs();

};


#endif //LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
