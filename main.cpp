//#include "program.cpp"
#include "testOperator.h"
//#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "circuit.h"

using namespace std;

void runProgram(circuit  c)
{
    c.sort_Cir_inputs();
    unordered_map<string, tuple <string, bool, int>> current_Outputs_Map;
    int test = 0;
    int prevInpIndex = 0;
    int current_time = 0;
    tuple<string, bool, int> backOfCirInputs;

    for (int i = 0; i < c.getcirInputs().size(); i++)
    {

        c.sort_Cir_inputs();
        int lastTime = 0;
        backOfCirInputs = c.getcirInputs().back();
        lastTime = get<2>(backOfCirInputs);

        while ((get<2>(c.getcirInputs()[i]) != current_time))
        {
            current_time++;
        }

        if (get<2>(c.getcirInputs()[i]) ==
            current_time)
        {

            current_time++;
            for (int j = i; j < c.getcirInputs().size();
                 j++)
            {

                i = j;

                auto &input = (c.getcirInputsREF())[j];
                string inputName = get<0>(input);

                (c.getcurrent_Inputs_MapREF())[inputName] = input;

                // call operator
                run_Operator_Test(c, current_time, current_Outputs_Map, prevInpIndex);

                c.sort_Cir_inputs();


                if (get<2>(c.getcirInputs()[j]) !=
                    get<2>(c.getcirInputs()[j + 1]))
                { // checks if any other inputs have same value of time
                    break;
                }
            }
        }

        test++;
    }

    for(auto x : c.getcirInputs())
    {
        cout<<get<0>(x)<<'\t'<<get<1>(x)<<'\t'<<get<2>(x)<<endl;
    }


}




int main(int argc, char **argv) {

    int x = 0;
    char y;



    do
    {
        x = 0;
        cout<<"Choose the circuit you would like to test: "<<endl;
        cout<<"1: Circuit 1"<<endl<<"2: Circuit 2"<<endl<<"3: Circuit 3"<<endl<<"4: Circuit 4"<<endl<<"5: Circuit 5"<<endl<<"6: Circuit 6"<<endl;
        cin>>x;
        if(x == 1)
        {
            //Circuit 1
            circuit c4;
            c4.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1 - Copy.txt");
            c4.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c4.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 1/circuit_1_sim.sim");
            runProgram(c4);
        }
        else if(x ==2)
        {
            //Circuit 2
            circuit c5;
            c5.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 2/test_circuit_2 - Copy.txt");
            c5.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c5.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 2/circuit_2_sim.sim");
            runProgram(c5);
        }
        else if(x == 3)
        {
            //Circuit 3
            circuit c1;
            c1.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 3/test_circuit_3 - Copy.txt");
            c1.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c1.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 3/testcircuit3.sim");
            runProgram(c1);
        } else if(x==4)
        {
            //Circuit 4
            circuit c2;
            c2.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 4/test_circuit_4 - Copy.txt");
            c2.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c2.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 4/testcircuit4.sim");
            runProgram(c2);
        }else if(x == 5)
        {
            //Circuit 5
            circuit c;
            c.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5 - Copy.txt");
            c.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/writeToSim.txt");
            runProgram(c);
        }
        else if(x==6)
        {
            circuit c3;
            c3.read_lib_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 6/test_circuit_6 - Copy.txt");
            c3.read_stim_file(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
            c3.write_to_sim(
                    "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 6/circuit 6.sim");
            runProgram(c3);
        }

        cout<<"Test another?(y/n) "<<endl;
        cin>>y;


    }while (y == 'y');













}
