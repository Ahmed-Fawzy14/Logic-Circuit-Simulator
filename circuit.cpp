//
// Created by Fawzy on 3/11/2024.
//

#include "circuit.h"

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
