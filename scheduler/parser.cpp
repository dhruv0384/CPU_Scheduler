#include "parser.h"
#include <iostream>

using namespace std;

void parseInput(vector<Process>& processes) {
    int numProcesses;
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i) {
        Process process;
        cin >> process.name >> process.arrivalTime >> process.burstTime >> process.priority;
        process.index = i;  // Assign the original index to track the process
        processes.push_back(process);
    }
}
