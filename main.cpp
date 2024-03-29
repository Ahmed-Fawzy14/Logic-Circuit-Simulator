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
#include "circuit.h"

typedef map<int, pair<vector<tuple<string, bool, int>>, queue<shared_ptr<Logic_Gate>>>> boss;

using namespace std;


//Changed int to bool

//Tests if a single gate has this input
bool input_exists(shared_ptr<Logic_Gate> &gate, string &Input_name, bool &val, int time) {
    for (auto &element : gate->getREF_cir_Input_Names()) {
        if (element.first == Input_name) {
            element.second = val;
           // cout << element.first << " now has value " << val << " in " << gate->getCirCompName() << " at time " << time << endl;
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
void update_cirInputs_names(circuit &c,boss &copyBB, boss &BB,int &time, map<string, int> counter)
{


    auto activityList = copyBB[time].second;
    auto &scheduledEvents = copyBB[time].first;
    auto &usedGatesPtr = c.getUsedGatesPtr();
    int isCounter = 0;


    //While the activity list is not empty

    while (!activityList.empty())
    {
        //Access the top element is Activity List
        auto &gate = copyBB[time].second.front();
        auto &gateBB = BB[time].second.front();


        for (int i = 0; i < scheduledEvents.size(); i++)
        {

            auto value = get<1>(copyBB[time].first[i]);
            string input_Name = get<0>(copyBB[time].first[i]);

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

            gateBB = gate;

        }

    }


}






void fill_scheduled_events(circuit &c, boss &BB)
{

    auto &inputs = c.getcirInputsREF();
    int i = 0;
    // auto element_0 = BB[0].first[0];
    // auto logic_0 = BB[0].second.front();
    // i is the index in cirInputs
    while (i != inputs.size())
    {
        // At the time in the current cirinput element, we added to its vector a tuple (current tuple in cirinputs)
        (BB[get<2>(inputs[i])].first).push_back(inputs[i]);
        //cout << "At time: " << get<2>(inputs[i]) << " with values name:" << get<0>((BB[get<2>(inputs[i])].first).back()) << '\t'<<"logic value: " << get<1>((BB[get<2>(inputs[i])].first).back()) << "time: "<<get<2>((BB[get<2>(inputs[i])].first).back()) << endl;
        i++;
    }


}

bool existsInQueue(boss BB, string componentName, int time)
{

    queue<shared_ptr<Logic_Gate>> checkQueue = BB[time].second;
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
void fillActivityList(circuit &c, boss &BB, int &time, map<string, int> &counter, boss &copyBB) {

    auto &pair = BB[time];
    auto &copyPair = copyBB[time];

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
                cout << "Added to copyActivityList: " << gatePtr->getCirCompName() << " at time: " << time << endl;
            }

            if (!existsInQueue(BB, componentName, time)) {
                if (input_exists_bool(gatePtr, input_Name, value)) {
                    // Additionally, if the gate isn't already in the activity list, add it
                    activityList.push(gatePtr);
                    cout << "Added to activityList: " << gatePtr->getCirCompName() << " at time: " << time << endl;
                }
            }
        }
    }
}


void addOutputsToScheduledEvents(boss &BB, int &time)
{

    auto &scheduledEvents = BB[time].first;
    auto activityList = BB[time].second;
    bool output;
    int newTime = 0;


    while(!activityList.empty())
    {

        shared_ptr<Logic_Gate> frontGate = activityList.front();
        activityList.pop();

        output = evaluate(frontGate, time);
        newTime = get_TimeStamp(frontGate, time);
        string outputName = frontGate->getCirOutputName();
        (BB[newTime].first).push_back(make_tuple(outputName, output, newTime));
        cout<<"output is: "<<output<<" for "<<outputName<<endl;

    }

}


void printConsolidatedBB(const boss& BB) {
    // Check if BB is empty
    if (BB.empty()) {
        std::cout << "BB is empty, no data to display." << std::endl;
        return;
    }

    std::cout << "Time\tEvents (Input/Output, Value)\n";

    // Iterate over each time step in BB
    for (const auto& timeEntry : BB) {
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
        for (const auto& event : consolidatedEvents) {
            std::cout << event.first << ": " << event.second << "; ";
        }
        std::cout << "\n";
    }
}


void runAlgorithm(circuit &c, boss &BB, int maxTime)
{

    boss copyBB;
    map<string, int> counter;
    c.updateUsedGatesPtr();
    vector<shared_ptr<Logic_Gate>> usedGates = c.getUsedGatesPtr(); // Assuming getREF_usedGates is updated


    copyBB = BB;
    for(auto &row : BB)
    {

        int time = row.first;
        if(time <= maxTime)
        {
            fillActivityList(c, BB,time, counter, copyBB);

            update_cirInputs_names(c,copyBB, BB,time, counter);

            addOutputsToScheduledEvents(BB, time);
            copyBB = BB;
        }
        else
        {

            cout<<"Maximum time for simulation reached."<<endl;
            printConsolidatedBB(BB);
            exit(0);
        }



    }



    printConsolidatedBB(BB);
}



int main()
{
    boss BB;
    vector<vector<string>> components;
    int x = 0;
    int maxTime = 0;

    cout<<"Choose which test circuit you want to run: "<<endl;
    cout<<"1: BB Test 1"<<endl<<"2: BB Test 2"<<endl<<"3: BB Test 3"<<endl<<"4: BB Test 4"<<
    endl<<"5: Test Circuit 1"<<endl<<"6: Test Circuit 2"<<endl<<"7: Test Circuit 3"<<endl<<
    "8: Test Circuit 4"<<endl<<"9: Test Circuit 5"<<endl<<"10: Test Circuit 6"<<endl;
    cin>>x;
    cout<<"What is the maximum time of the simulation: "<<endl;
    cin>>maxTime;

    if(x==1)
    {
        //BB Test 1
        circuit c4;

        //Reading Files
        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/cells.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/1.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/1.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);
    }
    else if(x==2)
    {
        //ERROR HANDLING
        //BB Test 2
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/cells.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/2.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_2.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);
    }
    else if(x==3)
    {
        //ERROR HANDLING
        //BB Test 3
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/cells.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/3.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/2(1).stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);
    }
    else if(x==4)
    {
        //BB Test 4
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/cells.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/4.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/2(1).stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }
    else if(x==5)
    {
        //Test Circuit 1
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_1.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_1.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }

    else if(x==6)
    {
        //Test Circuit 2
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_2.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_4.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }
    else if(x==7)
    {
        //Test Circuit 3
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_3.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_4.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }
    else if(x==8)
    {
        //Test Circuit 4
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_4.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_4.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }
    else if(x==9)
    {
        //Test Circuit 5
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_5.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_5.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB, maxTime);

    }
    else if(x==10)
    {
        //Test Circuit 6
        circuit c4;

        c4.read_lib_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/LibraryFile.lib",
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_6.cir");
        c4.read_stim_file(
                "C:/Users/Fawzy/Spring 2024/untitled/Test Circuits/Shalan Circuits/test_circuit_4.stim");
        //c4.write_to_sim(
        fill_scheduled_events(c4, BB);

        runAlgorithm(c4, BB , maxTime);

    }




    return 0;
}

