//
// Created by Fawzy on 3/11/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#include "Logic_Gate.h"

class circuit {
private:

    //This has all the circuit components
    //Traverse over allGates to fill this
    vector<Logic_Gate> usedGates;

    //This is the worst case propogation delay in ps
    int propgration_Delay_ps;


public:


};


#endif //LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
