#include "scheduler.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printResults(const vector<Process>& processes, const vector<int>& finishTime, const vector<int>& turnAroundTime, const vector<int>& waitingTime) {
    cout << "Process | Arrival | Burst | Finish | Turnaround | Waiting\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "  " << processes[i].name << "    |   " << processes[i].arrivalTime << "    |  " << processes[i].burstTime << "  |   " << finishTime[i] << "   |   " << turnAroundTime[i] << "     |   " << waitingTime[i] << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <algorithm>\n";
        return 1;
    }

    int algorithmChoice = stoi(argv[1]);

    vector<Process> processes;
    parseInput(processes);

    vector<int> finishTime(processes.size()), turnAroundTime(processes.size()), waitingTime(processes.size());

    switch (algorithmChoice) {
        case 1:
            firstComeFirstServe(processes, finishTime, turnAroundTime, waitingTime);
            break;
        case 3:
            shortestJobFirst(processes, finishTime, turnAroundTime, waitingTime);
            break;
        case 4:
            shortestRemainingTime(processes, finishTime, turnAroundTime, waitingTime);
            break;
        case 5:
            priorityScheduling(processes, finishTime, turnAroundTime, waitingTime);
            break;
        default:
            cerr << "Invalid algorithm choice\n";
            return 1;
    }

    printResults(processes, finishTime, turnAroundTime, waitingTime);

    int totalWaitingTime = 0, totalTurnaroundTime = 0, totalBurstTime = 0, totalTime = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnAroundTime[i];
        totalBurstTime += processes[i].burstTime;
        totalTime = max(totalTime, finishTime[i]);
    }

    float avgWaitingTime = (float)totalWaitingTime / processes.size();
    float avgTurnaroundTime = (float)totalTurnaroundTime / processes.size();
    float cpuUtilization = 100.0 * totalBurstTime / totalTime;

    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTurnaroundTime << endl;
    cout << "CPU Utilization: " << fixed << setprecision(2) << cpuUtilization << "%" << endl;

    return 0;
}
