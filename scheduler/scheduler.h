#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
};

void firstComeFirstServe(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void roundRobin(vector<Process>& processes, int quantum, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void shortestProcessNext(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
void shortestRemainingTime(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime);
// Other algorithms...

#endif // SCHEDULER_H
