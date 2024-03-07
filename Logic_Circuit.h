//
// Created by Fawzy on 3/7/2024.
//

#ifndef LOGIC_CIRCUIT_SIMULATOR_LOGIC_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_LOGIC_CIRCUIT_H
using namespace std;
#include <string>
#include <vector>

//Data Type which will be used for all logic gates
struct Gate {

    string name;
    string type;
    int number_of_inputs;
    int number_of_outputs;
    int delay_ps;

};


//Any circuit from the .cir file will be modelled as an object of this class
class Logic_Circuit {

private:
    //Inputs are read from the .cir file and stored here
    vector<string> inputs;
    bool output;
    //Objects of the struct Gate will be stored here based on the data from the .cir file
    vector<Gate> gates;

public:
    void read_Cir_File();

    //Will be used in 
    void send_To_LogicGate();

};


#endif //LOGIC_CIRCUIT_SIMULATOR_LOGIC_CIRCUIT_H
