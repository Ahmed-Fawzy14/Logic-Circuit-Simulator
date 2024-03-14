#include <fstream> // Including the fstream library to read files
#include <iostream> 
#include <string> // Including the string library to use string functions
#include <sstream> // Including the sstream library to store data from files into variables using delimiters
#include "circuit.cpp" // Including the circuit.cpp file to create an object for each circuit
#include "Logic_Gate.cpp" // Including the Logic_Gate.cpp file to create an object for each gate in the lib file
#include "unordered_map"
using namespace std;

unordered_map<string, Logic_Gate>  read_lib_file() // function to read lib file
{
// declaring an input stream and string variables
ifstream input;
string line, name, no_of_inputs, delay, expression;
    
 // Opening the libfile   
input.open("C:/Users/Power/Desktop/Project dd1/INV, 1, ~(i1), 50.txt");
    
// Creating an unordered map of the gates in the lib file
unordered_map<string, Logic_Gate> librarygates;

// A while loop to go through all the data in the lib file
while (getline(input, line)) 
{
    // Creating an istringstream object and initializing it with a string (line)
    istringstream subst(line);
    
    // Reading data from the lib file and storing each string in its respective variable
    getline(subst, name, ',');
    getline(subst, no_of_inputs, ',');
    getline(subst, expression, ',');
    getline(subst, delay, ',');
    
    // Looping over the string expression and storing each character in it in a seperate vector
    vector <string> Expressions(expression.length());
    for (int i = 0; i < expression.length(); i++)
    {
        Expressions[i] = expression[i];
    }
    // Constructing a Logic_Gate object and initializing its variables with the data from the lib file
    Logic_Gate* gate= new Logic_Gate(name, stoi(no_of_inputs), stoi(delay), Expressions);

        librarygates[name] = *gate; //adding the Logic_Gate object in the map of logic gates
    }    
    input.close(); // closing the lib file
    return librarygates;
    }

    vector<tuple<char, bool, int>> read_stim_file() // Reading data from stim file
    {
    // Declaring strings to store the data from the stim file
    string line, Input, value, timestamp;
    // Opening the stim file
    input.open("C:/Users/Power/Desktop/Project dd1/500, B, 1.txt");
    // Declaring a vector of tuples that store each input's name with its value and timestamp
    vector<tuple<char, bool, int>> inputs;
        
    // Looping until the end of the stim file to store all the data in the vector of tuples
    while (getline(input, line)) 
    {
        // Declaring stringstream object and initializing it with a string (line) to be used in reading the data using delimiters
        istringstream subst(line);
        // Reading the data from each line
        getline(subst, timestamp, ',');
        getline(subst, Input, ',');
        getline(subst, value, ',');
        
        char letter = Input[0]; // Storing the input's name into a char variable
        
        // Storing the data into a tuple 
        tuple<char, bool, int> I(letter,  stoi(value), stoi(timestamp));
        
        // Storing the tuple into the vector of tuples that represents the vector of inputs
        inputs.push_back(I);

    }
        return inputs;
    }

void run()
{
    circuit C;
    // C.setusedGates(v); // v should be replaced with the vector of gates from circ file
    C.setcirInputs(inputs);

    tuple <char, bool, int> temp = C.getcirInputs().back(); // Storing the last tuple of stimulus in a variable temp
    int time_end = get<2>(temp); // Storing the last timestamp in the stim file into the variable time_end to represent the end time of the simulation
    int clock_sim = 0; // A variable simulating the clock starting the time from zero
    int i = 0; // Initializing a variable at zero to be used in the  while loop
    int index_UsedGated = 0; // Initializing an index for the usedgates vector
    bool expression_Output = 0; // Initializing the expression output variable with zero
    
    // A while loop to respresent the simulation time 
    while (time_end != clock_sim)
    {
        vector <tuple <char, bool, int>> V = C.getcirInputs();
        auto element = V[i];
        clock_sim = get <2> (element);

        for (auto gate : C.getusedGates())
        {


            // Evaluating the boolean expression of the gate
            expression_Output = c.operator(index_UsedGated, c.get_cir_Input_Names);

            //Push the 
            v.push_back(, make_tuple(expression_Output, ))
            
         
            
                // need input from circ file
                if ( input exists )
                {
                    // store the output expression in (cirinputs) with the current time + delay
                    //
                    //This adds the expression_output but needs time in third and name of output from .cir used gates for first
            */ 
                   
                
 

        }
        vector<tuple<char, bool, int>> VE = C.getcirInputs();
        int time = get<2> (VE.back());
    
        // A condition to make sure that if the propagation delay of the output exceeds the time_end, time_end will be updated with the new value 
        // so that the loop continues 
        if (time > time_end)
        {
            time_end = time; 
        }

        i++; // Incrementing the index of the vector of cirInputs to move to the next input

    }
    vector <tuple <char, bool, int>> VE = C.getcirInputs(); // Storing the cirInputs vector in another vector VE in order to use its functions easily
    tuple <char, bool, int> Final_output = VE.back(); // Storing the last output in variable
    write_to_sim(C); // Writing the output of the simulation into a file (sim file)
    
}

int main()
{

///////Testing

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
        
        v = C.getcirInputs(); // Storing the cirinputs in the vector v\
        
        ofstream output; // Declaring an ofstream object to write the output into the file
        
        output.open("sim.txt"); // Opening the file in which the output will be written

        // A loop to write the output in the format of a sim file (timestamp, input_name, value)
        for(int i = 0; i < v.size(); i++)
        {
            auto element = v[i];
            output <<  get<2> (element) << " " << get<0> (element) << " " << get<1> (element) << endl;

        }
    }
        
