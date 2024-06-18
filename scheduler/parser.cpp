#include "parser.h"
#include <iostream>

using namespace std;

void parseInput(vector<Process>& processes) {
    int numProcesses;
    cin >> numProcesses;

    // Debugging: Confirm input size
    cout << "Number of Processes: " << numProcesses << endl;

    for (int i = 0; i < numProcesses; ++i) {
        Process process;
        cin >> process.name >> process.arrivalTime >> process.burstTime >> process.priority;
        process.index = i;  // Assign the original index to track the process
        processes.push_back(process);
    }

    // Debugging: Print parsed processes
    cout << "Parsed Processes:\n";
    for (const auto& process : processes) {
        cout << "Name: " << process.name << ", Arrival: " << process.arrivalTime << ", Burst: " << process.burstTime << ", Priority: " << process.priority << "\n";
    }
}
