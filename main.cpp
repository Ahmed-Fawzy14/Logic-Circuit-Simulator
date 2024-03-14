#include <fstream> // Including the fstream library to read files
#include <iostream> // Including the iostream library in case of couting any output for debugging or clarity purposes
#include <string> // Including the string library to use string functions
#include <sstream> // Including the sstream library to store data from files into variables using delimiters
#include "circuit.cpp" // Including the circuit.cpp file to create an object for each circuit
#include "Logic_Gate.cpp" // Including the Logic_Gate.cpp file to create an object for each gate in the lib file
#include "unordered_map" // Including the unordered_map class to be used in the storing of gates
using namespace std;


int main()
{

///////Testing
    vector <Logic_Gate> all_gates = read_lib_file();
    
    circuit c1;
    c1.read_lib_file();
    c1.readfile();
    c1.run();
    circuit c2;
    c2.read_lib_file();
    c2.readfile();
    c2.run();
    circuit c3;
    c3.read_lib_file();
    c3.readfile();
    c3.run();
    circuit c4;
    c4.read_lib_file();
    c4.readfile();
    c4.run();
    circuit c5;
    c5.read_lib_file();
    c5.readfile();
    c5.run();
    circuit c6;
    c6.read_lib_file();
    c6.readfile();
    c6.run();
ifstream inputfile;
    inputfile.open(".cir_file"); // opening the file
    readfile(inputfile);

    // 2d vector delaration
    vector<vector<string>> components;
    fillvector(components, inputfile);

    objectmodification(components);

    
    return 0;
}

    // A function to write the output into a file (sim file)
    void write_to_sim(circuit C)
    {
        vector<tuple <char, bool, int>> v; // Declaring a vector of tuples to store the cirinputs for simplicity
        
        v = C.getcirInputs(); // Storing the cirinputs in the vector v
        
        ofstream output; // Declaring an ofstream object to write the output into the file
        
        output.open("sim.txt"); // Opening the file in which the output will be written

        // A loop to write the output in the format of a sim file (timestamp, input_name, value)
        for(int i = 0; i < v.size(); i++)
        {
            auto element = v[i];
            output <<  get<2> (element) << " " << get<0> (element) << " " << get<1> (element) << endl;

        }
    }
        
