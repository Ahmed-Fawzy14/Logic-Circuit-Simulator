#include "runProgram.cpp"

int main() {

    char y;

   do
   {
       EventDriven allStructures;
       circuit c;
       string libFilePath, cirFilePath, stimFilePath;
       int maxTime;

       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this line


       cout << "Enter the path to the library file: "<<endl;
       getline(cin, libFilePath); // Use getline to allow spaces in the path

       cout << "Enter the path to the circuit file: "<<endl;
       getline(cin, cirFilePath);

       cout << "Enter the path to the stimulus file: "<<endl;
       getline(cin, stimFilePath);

       cout << "What is the maximum time of the simulation? "<<endl;
       cin >> maxTime;

       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this right before the first getline if not immediately after a previous cin >> input


       // Assuming read_lib_file, read_stim_file are member functions of the 'circuit' class and take care of file reading.
       c.readLibFile(libFilePath, cirFilePath);
       c.readStimFile(stimFilePath);

       // Now, you would proceed with your simulation logic
       fill_scheduled_events(c, allStructures);
       runAlgorithm(c, allStructures, maxTime);

       cout<<"Simulate another circuit? (y/n) "<<endl;
       cin>>y;
   }while(y == 'y');


    return 0;
}
