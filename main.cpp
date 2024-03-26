// #include "program.cpp"
#include "testOperator.h"
// #include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include "circuit.h"
typedef map<int, pair<vector<tuple<string, bool, int>>, queue<Logic_Gate>>> boss;
typedef pair<vector<tuple<string, bool, int>>, queue<Logic_Gate>> Pair;
using namespace std;
void fill_scheduled_events(circuit &c, boss &BB)
{
        queue<Logic_Gate> qu;
        auto &inputs = c.getcirInputsREF();
        int i = 0;
        auto element_0 = BB[0].first[0];
        auto logic_0 = BB[0].second.front();
        // i is the index in cirInputs
        while (i != inputs.size())
        {
                // At the time in the current cirinput element, we added to its vector a tuple(current tuple in cirinputs)

                (BB[get<2>(inputs[i])].first).push_back(inputs[i]);
                cout << "At time: " << get<2>(inputs[i]) << " with values" << get<0>((BB[get<2>(inputs[i])].first).back()) << '\t' << get<1>((BB[get<2>(inputs[i])].first).back()) << get<2>((BB[get<2>(inputs[i])].first).back()) << endl;
        }
}
// void preoperator(circuit &c)
// {
//         boss BB;
//         int i = 0;
// vector<vector<string>> &components;
//         string file_name = ("C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/LibraryFile.lib");
//         c.read_lib_file("C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/LibraryFile.lib", file_name);
//         c.read_stim_file("C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1 - circuit file.txt");
//         c.fillvector(components, "C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1.cir");

//         while (i != BB[])
//         {

//                 auto element_0 = BB[0].first[0];
//                 auto logic_0 = BB[0].second.front();

//                 cout << "Current element(s) from scheduled events:" << '\t' << get<0>(element_0);
//                 cout << "Current act list:" << '\t' << logic_0.getCirCompName();
//         }
// }
int main()
{
        circuit c1;
        boss BB;
        vector<vector<string>> components;

        string file_name = ("C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/LibraryFile.lib");
        c1.read_lib_file("C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/LibraryFile.lib",
                         "C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1 - circuit file.txt");
        c1.read_stim_file("C:/UsersPower/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1.stim");
        // c1.fillvector(components, "C:/Users/Power/Documents/GitHub/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1 - circuit file.txt");
        fill_scheduled_events(c1, BB);
        // preoperator(c1);
        return 0;
}

// int main(int argc, char **argv)
// {

//         int x = 0;
//         char y;

//         do
//         {
//                 x = 0;
//                 cout << "Choose the circuit you would like to test: " << endl;
//                 cout << "1: Circuit 1" << endl
//                      << "2: Circuit 2" << endl
//                      << "3: Circuit 3" << endl
//                      << "4: Circuit 4" << endl
//                      << "5: Circuit 5" << endl
//                      << "6: Circuit 6" << endl;
//                 cin >> x;
//                 if (x == 1)
//                 {
//                         // Circuit 1
//                         circuit c4;
//                         c4.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 1/test_circuit_1 - Copy.txt");
//                         c4.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c4.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 1/circuit_1_sim.sim");
//                         runProgram(c4);
//                 }
//                 else if (x == 2)
//                 {
//                         // Circuit 2
//                         circuit c5;
//                         c5.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 2/test_circuit_2 - Copy.txt");
//                         c5.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c5.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 2/circuit_2_sim.sim");
//                         runProgram(c5);
//                 }
//                 else if (x == 3)
//                 {
//                         // Circuit 3
//                         circuit c1;
//                         c1.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 3/test_circuit_3 - Copy.txt");
//                         c1.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c1.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 3/testcircuit3.sim");
//                         runProgram(c1);
//                 }
//                 else if (x == 4)
//                 {
//                         // Circuit 4
//                         circuit c2;
//                         c2.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 4/test_circuit_4 - Copy.txt");
//                         c2.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c2.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 4/testcircuit4.sim");
//                         runProgram(c2);
//                 }
//                 else if (x == 5)
//                 {
//                         // Circuit 5
//                         circuit c;
//                         c.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5 - Copy.txt");
//                         c.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/writeToSim.txt");
//                         runProgram(c);
//                 }
//                 else if (x == 6)
//                 {
//                         circuit c3;
//                         c3.read_lib_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/LibraryFile.lib",
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 6/test_circuit_6 - Copy.txt");
//                         c3.read_stim_file(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 5/test_circuit_5.stim");
//                         c3.write_to_sim(
//                             "C:/Users/Fawzy/Spring 2024/Digital Design I/Project 1/Logic-Circuit-Simulator/Test Circuits/Circuit 6/circuit 6.sim");
//                         runProgram(c3);
//                 }

//                 cout << "Test another?(y/n) " << endl;
//                 cin >> y;

//         } while (y == 'y');
// }
