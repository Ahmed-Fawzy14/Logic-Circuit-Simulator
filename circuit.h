//
// Created by Fawzy on 3/11/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#include "Logic_Gate.h"
#include <unordered_map>

#include <queue>
#include "Logic_Gate.cpp"

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

     vector<tuple<char, bool, int>> cirInputs;


public:



    void Run();

    //Send the index of the object in usedGates to this function and the current cir_Input_Names
    bool Operator(int index,  vector<pair<string,int>> cir_Input_Names)
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
                    output = output & ((y.second).second & (y.second).second);
            }
        }


        return 0;
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
