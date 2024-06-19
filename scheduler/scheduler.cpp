#include "scheduler.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// First Come First Serve
void firstComeFirstServe(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        int processIndex = i;
        int arrivalTime = processes[i].arrivalTime;
        int burstTime = processes[i].burstTime;

        if (time < arrivalTime) {
            time = arrivalTime;
        }

        time += burstTime;
        finishTime[processIndex] = time;
        turnAroundTime[processIndex] = finishTime[processIndex] - arrivalTime;
        waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime;

        time += contextSwitchTime;
    }
}

// Shortest Job First
void shortestJobFirst(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime || (a.burstTime == b.burstTime && a.arrivalTime < b.arrivalTime);
    });

    finishTime[0] = processes[0].arrivalTime + processes[0].burstTime;
    turnAroundTime[0] = finishTime[0] - processes[0].arrivalTime;
    waitingTime[0] = turnAroundTime[0] - processes[0].burstTime;

    for (size_t i = 1; i < processes.size(); ++i) {
        finishTime[i] = finishTime[i - 1] + processes[i].burstTime + contextSwitchTime;
        turnAroundTime[i] = finishTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnAroundTime[i] - processes[i].burstTime;
    }
}

// Shortest Remaining Time
void shortestRemainingTime(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    auto comp = [](const Process& a, const Process& b) {
        return a.burstTime > b.burstTime;
    };
    priority_queue<Process, vector<Process>, decltype(comp)> pq(comp);
    vector<int> remainingTime(processes.size());
    int time = 0;

    for (size_t i = 0; i < processes.size(); ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    size_t i = 0;
    while (!pq.empty() || i < processes.size()) {
        while (i < processes.size() && processes[i].arrivalTime <= time) {
            pq.push(processes[i]);
            i++;
        }

        if (!pq.empty()) {
            Process current = pq.top();
            pq.pop();

            int executionTime = 1;
            time += executionTime;
            remainingTime[current.index] -= executionTime;

            if (remainingTime[current.index] > 0) {
                pq.push(current);
            } else {
                finishTime[current.index] = time;
                turnAroundTime[current.index] = finishTime[current.index] - current.arrivalTime;
                waitingTime[current.index] = turnAroundTime[current.index] - current.burstTime;
            }

            time += contextSwitchTime;
        } else {
            time++;
        }
    }
}

// Priority Scheduling
void priorityScheduling(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    auto comp = [](const Process& a, const Process& b) {
        return a.priority > b.priority;
    };
    priority_queue<Process, vector<Process>, decltype(comp)> pq(comp);
    int time = 0;

    size_t i = 0;
    while (!pq.empty() || i < processes.size()) {
        while (i < processes.size() && processes[i].arrivalTime <= time) {
            pq.push(processes[i]);
            i++;
        }

        if (!pq.empty()) {
            Process current = pq.top();
            pq.pop();

            int executionTime = min(current.burstTime, 1);
            time += executionTime;
            current.burstTime -= executionTime;

            if (current.burstTime > 0) {
                pq.push(current);
            } else {
                finishTime[current.index] = time;
                turnAroundTime[current.index] = finishTime[current.index] - current.arrivalTime;
                waitingTime[current.index] = turnAroundTime[current.index] - current.burstTime;
            }

            time += contextSwitchTime;
        } else {
            time++;
        }
    }
}
