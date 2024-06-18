#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>

using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
    int priority; // Added for priority scheduling
    int index;    // To track original index

    // Define operator== to compare processes
    bool operator==(const Process& other) const {
        return name == other.name && arrivalTime == other.arrivalTime && burstTime == other.burstTime && priority == other.priority;
    }
};

void firstComeFirstServe(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime);
void roundRobin(vector<Process>& processes, int contextSwitchTime, int quantum, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime);
void shortestJobFirst(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime);
void shortestRemainingTime(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime);
void priorityScheduling(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime);

#endif // SCHEDULER_H
