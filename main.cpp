#include "program.cpp"
using namespace std;


int main()
{

    //Reading all the gates from the .lib file
    vector <Logic_Gate> all_gates = read_lib_file();

//Reading the .cir file
    ifstream inputfile;
    inputfile.open(".cir_file"); // opening the file
    readfile(inputfile);

    // 2d vector delaration
    //Combining data from .cir and .lib only to the gates used
    vector<vector<string>> components;
    fillvector(components, inputfile);

    objectmodification(components);


    //Testing each ciruit 
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

    
    return 0;
}


        
