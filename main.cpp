#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "circuit.cpp"
#include "Logic_Gate.cpp"
using namespace std;

int main()
{
ifstream input;
string line, name, no_of_inputs, delay, expression;
input.open("C:/Users/Power/Desktop/Project dd1/INV, 1, ~(i1), 50.txt");
vector <Logic_Gate> v;
while (getline(input, line)) 
{

    istringstream subst(line);
    getline(subst, name, ',');
    getline(subst, no_of_inputs, ',');
    getline(subst, expression, ',');
    getline(subst, delay, ',');
    vector <string> Expressions(expression.length());
    for (int i = 0; i < expression.length(); i++)
    {
        Expressions[i] = expression[i];
    }
    Logic_Gate* gate= new Logic_Gate(name, stoi(no_of_inputs), stoi(delay), Expressions);
    v.push_back(*gate);
    }    
    input.close();

    string line, Input, value, timestamp;
    input.open("C:/Users/Power/Desktop/Project dd1/500, B, 1.txt");
    vector<tuple<char, bool, int>> inputs;

    while (getline(input, line)) 
    {

        istringstream subst(line);
        getline(subst, timestamp, ',');
        getline(subst, Input, ',');
        getline(subst, value, ',');
        char letter = Input[0];

        tuple<char, bool, int> I(letter,  stoi(value), stoi(timestamp));
        inputs.push_back(I);

    }
    circuit C;
    C.setusedGates(v); // v should be replaced with the vector of gates from circ file
    C.setcirInputs(inputs);

    tuple <char, bool, int> temp = C.getcirInputs().back();
    int time_end = get<2>(temp);
    int clock_sim = 0;
    int i = 0;
    int index_UsedGated = 0;
    bool expression_Output = 0;
    while (time_end != clock_sim)
    {
        vector <tuple <char, bool, int>> V = C.getcirInputs();
        auto element = V[i];
        clock_sim = get <2> (element);

        for (auto gate : C.getusedGates())
        {



            expression_Output = c.operator(index_UsedGated, c.get_cir_Input_Names);

            
           /* for ()
            {
                // need input from circ file
                if ( input exists )
                {
                    // store the output expression in (cirinputs) with the current time + delay
                    //
                    //This adds the expression_output but needs time in third and name of output from .cir used gates for first 
                    v.push_back(, make_tuple(expression_Output, ))
                }

            }*/
            

            

        }
        vector<tuple<char, bool, int>> VE = C.getcirInputs();
        int time = get<2> (VE.back());
        if (time > clock_sim)
        {
            time_end = time;
        }

        i++;

    }
    vector <tuple <char, bool, int>> VE = C.getcirInputs();
    tuple <char, bool, int> Final_output = VE.back();
    write_to_sim(C);
    



    return 0;
}
    void write_to_sim(circuit C)
    {
        vector<tuple <char, bool, int>> v;
        v = C.getcirInputs(); 
        ofstream output;
        output.open("sim.txt");

        for(int i = 0; i < v.size(); i++)
        {
            auto element = v[i];
            output <<  get<2> (element) << " " << get<0> (element) << " " << get<1> (element) << endl;

        }
    }
        
