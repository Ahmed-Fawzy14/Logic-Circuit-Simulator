//
// Created by Fawzy on 3/11/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#include <queue>
#include "Logic_Gate.cpp"

class circuit {
private:

    //This has all the circuit components
    //Traverse over allGates to fill this
    //Use the vector for flagging method 
    vector<Logic_Gate> usedGates;
    //Use the Queue for popping method 
    queue<Logic_Gate> usedGates;

    //This is the worst case propogation delay in ps
    int propgration_Delay_ps;

    //This is the final time in the .stim file
    int time_End;

     vector<tuple<char, bool, int>> cirInputs;


public:



    void Run();

    bool Operator()
    {
        //will use usedGates[i].expression to access what is needed
    }
    void setusedGates(vector <Logic_Gate> gates)
    {
        usedGates = gates;
    }

    void setcirInputs(vector<tuple<char, bool, int>> inputs)
    {
        cirInputs = inputs;
    }

    vector <Logic_Gate> getusedGates()
    {
       return usedGates;
    }

    vector <tuple<char, bool, int>> getcirInputs()
    {
        return cirInputs;
    }

    
};


#endif //LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
