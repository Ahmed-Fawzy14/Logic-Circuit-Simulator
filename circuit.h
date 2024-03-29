#ifndef LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
#define LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H

#include "Logic_Gate.h"
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <tuple>

using namespace std;

class circuit {
private:
    vector<Logic_Gate> usedGates; // Holds all the circuit components
    vector<shared_ptr<Logic_Gate>> usedGatesPtr; // Shared pointers to Logic_Gate objects for dynamic memory management
    int propagationDelayPs; // Worst-case propagation delay in picoseconds
    int timeEnd; // Final time in the .stim file
    vector<tuple<string, bool, int>> cirInputs; // Circuit inputs
    map<string, Logic_Gate> allGates; // All gates in the circuit
    vector<string> cir_Inputs;

public:
    // Member function declarations
    void updateUsedGatesPtr();
    vector<shared_ptr<Logic_Gate>>& getUsedGatesPtr();
    void setAllGates(const map<string, Logic_Gate>& libraryGates);
    const map<string, Logic_Gate>& getAllGates() const;
    vector<tuple<string, bool, int>>& getCirInputsRef();
    void setUsedGates(const vector<Logic_Gate>& gates);
    void pushGateInUsedGates(const Logic_Gate& gate);
    void setCirInputs(const vector<tuple<string, bool, int>>& inputs);
    void objectModification(vector<vector<string>>& components);
    void fillVector(vector<vector<string>>& components, const string& fileName);
    vector<Logic_Gate> getUsedGates() const;
    vector<Logic_Gate>& getRefUsedGates();
    vector<tuple<string, bool, int>> getCirInputs() const;
    void readLibFile( const string& filepath, const string& fileName);
    void readStimFile(const string& filepath);
    bool isOutputOfPreviousGate(string output, vector<Logic_Gate> &previousGates);
    void sortCirInputs();
    int usedGatessize() const;
};

#endif // LOGIC_CIRCUIT_SIMULATOR_CIRCUIT_H
