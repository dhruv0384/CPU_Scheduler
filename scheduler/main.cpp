#include "scheduler.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printResults(const vector<Process>& processes, const vector<int>& finishTime, const vector<int>& turnAroundTime, const vector<int>& waitingTime, const vector<int>& responseTime) {
    cout << "Process | Arrival | Burst | Finish | Turnaround | Waiting | Response\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "  " << processes[i].name << "    |   " << processes[i].arrivalTime << "    |  " << processes[i].burstTime << "  |   " << finishTime[i] << "   |   " << turnAroundTime[i] << "     |   " << waitingTime[i] << "   |   " << responseTime[i] << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <algorithm> <context_switch_time>\n";
        return 1;
    }

    int algorithmChoice = stoi(argv[1]);
    int contextSwitchTime = stoi(argv[2]);
    int timeQuantum = 0;

    if (algorithmChoice == 2 && argc == 4) {
        timeQuantum = stoi(argv[3]);
    }

    vector<Process> processes;
    parseInput(processes);

    vector<int> finishTime(processes.size()), turnAroundTime(processes.size()), waitingTime(processes.size()), responseTime(processes.size());

    switch (algorithmChoice) {
        case 1:
            firstComeFirstServe(processes, contextSwitchTime, finishTime, turnAroundTime, waitingTime, responseTime);
            break;
        case 2:
            roundRobin(processes, contextSwitchTime, timeQuantum, finishTime, turnAroundTime, waitingTime, responseTime);
            break;
        case 3:
            shortestJobFirst(processes, contextSwitchTime, finishTime, turnAroundTime, waitingTime, responseTime);
            break;
        case 4:
            shortestRemainingTime(processes, contextSwitchTime, finishTime, turnAroundTime, waitingTime, responseTime);
            break;
        case 5:
            priorityScheduling(processes, contextSwitchTime, finishTime, turnAroundTime, waitingTime, responseTime);
            break;
        default:
            cerr << "Invalid algorithm choice\n";
            return 1;
    }

    printResults(processes, finishTime, turnAroundTime, waitingTime, responseTime);

    return 0;
}
