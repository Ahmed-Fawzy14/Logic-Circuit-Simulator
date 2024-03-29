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
#include <stack>
#include <limits>
#include "circuit.h"
//TimeStack, Scheduled Events, Activity List
typedef map<int, pair<vector<tuple<string, bool, int>>, queue<shared_ptr<Logic_Gate>>>> EventDriven;

using namespace std;



//Tests if a single gate has this input
bool input_exists(shared_ptr<Logic_Gate> &gate, string &Input_name, bool &val, int time) {
    for (auto &element : gate->getREF_cir_Input_Names()) {
        if (element.first == Input_name) {
            element.second = val;
            return true;
        }
    }
    return false;
}
bool input_exists_bool(shared_ptr<Logic_Gate> &gate, string &Input_name, bool &val)
{
    for (auto &element : gate->getREF_cir_Input_Names())
    {
        //Here we are checking if at least one element exists
        if ((element.first == Input_name))
        {
            return true;
        }
    }
    return false;
}


//Changed get<2> to get<1> since it should pass bool
void update_cirInputs_names(circuit &c,EventDriven &copyallStructures, EventDriven &allStructures,int &time, map<string, int> counter)
{


    auto activityList = copyallStructures[time].second;
    auto &scheduledEvents = copyallStructures[time].first;
    auto &usedGatesPtr = c.getUsedGatesPtr();
    int isCounter = 0;


    //While the activity list is not empty

    while (!activityList.empty())
    {
        //Access the top element is Activity List
        auto &gate = copyallStructures[time].second.front();
        auto &gateallStructures = allStructures[time].second.front();


        for (int i = 0; i < scheduledEvents.size(); i++)
        {

            auto value = get<1>(copyallStructures[time].first[i]);
            string input_Name = get<0>(copyallStructures[time].first[i]);

            //We know that at least one inputs exists so here we know a value must be changed or added
            if(input_exists(gate, input_Name,  value, time))
            {
                for(auto& x: usedGatesPtr)
                {
                    for(auto &y : x->getREF_cir_Input_Names())
                    {

                        for(auto &z : gate->getREF_cir_Input_Names())
                        {
                            if(y.first == z.first)
                            {
                                //Does update it but something is bringing it back to 0
                                y.second = z.second;

                            }
                        }
                    }
                }


                //The gate in the actitvity list should get the new cir Input names here
                //So I will do gate in activity list . set cir input names to the current one
                if(!activityList.empty())
                    activityList.pop();

            }

            gateallStructures = gate;

        }

    }


}






void fill_scheduled_events(circuit& c, EventDriven& allStructures) {
    auto& inputs = c.getCirInputsRef();
    for (int i = 0; i < inputs.size(); ++i) {
        allStructures[get<2>(inputs[i])].first.push_back(inputs[i]);
    }
}


bool existsInQueue(EventDriven allStructures, string componentName, int time)
{

    queue<shared_ptr<Logic_Gate>> checkQueue = allStructures[time].second;
    stack<string> compName;

    while(!checkQueue.empty())
    {
        shared_ptr<Logic_Gate> element = checkQueue.front();
        checkQueue.pop();
        if(element->getCirCompName() == componentName)
            return true;

    }

    return false;

}

//This adds all elements to the activity list; Should be called at any time when there is an event in scheduled events
void fillActivityList(circuit &c, EventDriven &allStructures, int &time, map<string, int> &counter, EventDriven &copyallStructures) {

    auto &pair = allStructures[time];
    auto &copyPair = copyallStructures[time];

    auto &scheduledEvents = pair.first;
    auto &activityList = pair.second;
    auto &copyActivityList = copyPair.second;

    for (int i = 0; i < scheduledEvents.size(); i++) {
        auto &event = scheduledEvents[i];
        string input_Name = get<0>(event);
        auto value = get<1>(event);

        for (auto &gatePtr : c.getUsedGatesPtr()) {
            string componentName = gatePtr->getCirCompName();

            if (input_exists_bool(gatePtr, input_Name, value)) {
                // If gate meets criteria, add it to the copyActivityList
                copyActivityList.push(gatePtr);
            }

            if (!existsInQueue(allStructures, componentName, time)) {
                if (input_exists_bool(gatePtr, input_Name, value)) {
                    // Additionally, if the gate isn't already in the activity list, add it
                    activityList.push(gatePtr);
                }
            }
        }
    }
}


void addOutputsToScheduledEvents(EventDriven &allStructures, int &time)
{

    auto &scheduledEvents = allStructures[time].first;
    auto activityList = allStructures[time].second;
    bool output;
    int newTime = 0;


    while(!activityList.empty())
    {

        shared_ptr<Logic_Gate> frontGate = activityList.front();
        activityList.pop();

        output = evaluate(frontGate, time);
        newTime = get_TimeStamp(frontGate, time);
        string outputName = frontGate->getCirOutputName();
        (allStructures[newTime].first).push_back(make_tuple(outputName, output, newTime));

    }

}


void printConsolidatedallStructures(const EventDriven& allStructures) {
    // Open a file in write mode.
    std::ofstream outFile("C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/circuit_1_sim.sim");

    // Check if allStructures is empty
    if (allStructures.empty()) {
        std::cout << "allStructures is empty, no data to display." << std::endl;
        // Write the same message to the file
        outFile << "allStructures is empty, no data to display." << std::endl;
        return;
    }

    std::cout << "Time\tEvents (Input/Output, Value)\n";
    // Write the same header to the file
    outFile << "Time\tEvents (Input/Output, Value)\n";

    // Iterate over each time step in allStructures
    for (const auto& timeEntry : allStructures) {
        int time = timeEntry.first;
        const auto& events = timeEntry.second.first; // The vector of events

        // Use a map to track the latest value for each signal at this time step
        std::map<std::string, bool> consolidatedEvents;

        // Populate consolidatedEvents with the latest value of each signal
        for (const auto& event : events) {
            std::string name = std::get<0>(event); // Input/Output name
            bool value = std::get<1>(event); // The boolean value
            consolidatedEvents[name] = value;
        }

        // Now print the consolidated events for this time step
        std::cout << time << "\t";
        // Write the same info to the file
        outFile << time << "\t";
        for (const auto& event : consolidatedEvents) {
            std::cout << event.first << ": " << event.second << "; ";
            // Write the same info to the file
            outFile << event.first << ": " << event.second << "; ";
        }
        std::cout << "\n";
        outFile << "\n"; // Write a newline to the file as well
    }
}


void runAlgorithm(circuit &c, EventDriven &allStructures, int maxTime)
{

    EventDriven copyallStructures;
    map<string, int> counter;
    c.updateUsedGatesPtr();
    vector<shared_ptr<Logic_Gate>> usedGates = c.getUsedGatesPtr(); // Assuming getREF_usedGates is updated


    copyallStructures = allStructures;
    for(auto &row : allStructures)
    {

        int time = row.first;
        if(time <= maxTime)
        {
            fillActivityList(c, allStructures,time, counter, copyallStructures);

            update_cirInputs_names(c,copyallStructures, allStructures,time, counter);

            addOutputsToScheduledEvents(allStructures, time);
            copyallStructures = allStructures;
        }
        else
        {

            cout<<"Maximum time for simulation reached."<<endl;
            printConsolidatedallStructures(allStructures);
            exit(0);
        }



    }



    printConsolidatedallStructures(allStructures);
}


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
