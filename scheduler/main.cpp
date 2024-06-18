// #include "scheduler.h"
// #include "parser.h"
// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;

// void printResults(const vector<Process>& processes, const vector<int>& finishTime, const vector<int>& turnAroundTime, const vector<int>& waitingTime) {
//     cout << "Process | Arrival | Burst | Finish | Turnaround | Waiting\n";
//     for (size_t i = 0; i < processes.size(); ++i) {
//         cout << "  " << processes[i].name << "    |   " << processes[i].arrivalTime << "    |  " << processes[i].burstTime << "  |   " << finishTime[i] << "   |   " << turnAroundTime[i] << "     |   " << waitingTime[i] << "\n";
//     }
// }

// int main(int argc, char* argv[]) {
//     if (argc < 3) {
//         cerr << "Usage: " << argv[0] << " <algorithm> <context_switch_time>\n";
//         return 1;
//     }

//     int algorithmChoice = stoi(argv[1]);
//     int contextSwitchTime = stoi(argv[2]);

//     vector<Process> processes;
//     parseInput(processes);

//     vector<int> finishTime(processes.size()), turnAroundTime(processes.size()), waitingTime(processes.size());

//     switch (algorithmChoice) {
//         case 1:
//             firstComeFirstServe(processes, finishTime, turnAroundTime, waitingTime);
//             break;
//         case 2:
//             int quantum;
//             cout << "Enter time quantum: ";
//             cin >> quantum;
//             roundRobin(processes, quantum, finishTime, turnAroundTime, waitingTime);
//             break;
//         // Other cases...
//         default:
//             cerr << "Invalid algorithm choice\n";
//             return 1;
//     }

//     printResults(processes, finishTime, turnAroundTime, waitingTime);

//     return 0;
// }

#include "scheduler.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printResults(const vector<Process>& processes, const vector<int>& finishTime, const vector<int>& turnAroundTime, const vector<int>& waitingTime) {
    cout << "Process | Arrival | Burst | Finish | Turnaround | Waiting\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "  " << processes[i].name << "    |   " << processes[i].arrivalTime << "    |  " << processes[i].burstTime << "  |   " << finishTime[i] << "   |   " << turnAroundTime[i] << "     |   " << waitingTime[i] << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <algorithm> <context_switch_time>\n";
        return 1;
    }

    int algorithmChoice = stoi(argv[1]);
    int contextSwitchTime = stoi(argv[2]);

    vector<Process> processes;
    parseInput(processes);

    // Debugging: Confirm input parsing
    cout << "Parsed " << processes.size() << " processes.\n";

    vector<int> finishTime(processes.size()), turnAroundTime(processes.size()), waitingTime(processes.size());

    switch (algorithmChoice) {
        case 1:
            firstComeFirstServe(processes, finishTime, turnAroundTime, waitingTime);
            break;
        case 2:
            int quantum;
            cout << "Enter time quantum: ";
            cin >> quantum;
            roundRobin(processes, quantum, finishTime, turnAroundTime, waitingTime);
            break;
        // Other cases...
        default:
            cerr << "Invalid algorithm choice\n";
            return 1;
    }

    printResults(processes, finishTime, turnAroundTime, waitingTime);

    return 0;
}
