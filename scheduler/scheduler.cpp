#include "scheduler.h"
#include <algorithm>
#include <iostream>

using namespace std;

void firstComeFirstServe(vector<Process>& processes, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    int time = processes[0].arrivalTime;
    for (size_t i = 0; i < processes.size(); ++i) {
        int processIndex = i;
        int arrivalTime = processes[i].arrivalTime;
        int burstTime = processes[i].burstTime;

        finishTime[processIndex] = (time + burstTime);
        turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
        waitingTime[processIndex] = (turnAroundTime[processIndex] - burstTime);

        time += burstTime;
    }
}

void roundRobin(vector<Process>& processes, int quantum, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    queue<pair<int, int> > q;
    vector<int> remainingTime(processes.size());

    for (size_t i = 0; i < processes.size(); ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    int time = 0;
    size_t i = 0;
    while (!q.empty() || i < processes.size()) {
        if (!q.empty()) {
            pair<int, int> front = q.front();
            int processIndex = front.first;
            int remainingBurst = front.second;
            q.pop();

            int executionTime = min(remainingBurst, quantum);
            time += executionTime;
            remainingTime[processIndex] -= executionTime;

            if (remainingTime[processIndex] > 0) {
                q.push(make_pair(processIndex, remainingTime[processIndex]));
            } else {
                finishTime[processIndex] = time;
                turnAroundTime[processIndex] = finishTime[processIndex] - processes[processIndex].arrivalTime;
                waitingTime[processIndex] = turnAroundTime[processIndex] - processes[processIndex].burstTime;
            }
        }

        while (i < processes.size() && processes[i].arrivalTime <= time) {
            q.push(make_pair(i, remainingTime[i]));
            ++i;
        }

        if (q.empty() && i < processes.size()) {
            time = processes[i].arrivalTime;
        }
    }
}

// Other scheduling algorithms...
