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

void firstComeFirstServe(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void shortestJobFirst(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void shortestRemainingTime(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void priorityScheduling(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);

#endif // SCHEDULER_H
