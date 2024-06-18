#include "scheduler.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

void firstComeFirstServe(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime) {
    int time = processes[0].arrivalTime;
    for (size_t i = 0; i < processes.size(); ++i) {
        int processIndex = i;
        int arrivalTime = processes[i].arrivalTime;
        int burstTime = processes[i].burstTime;

        if (time < arrivalTime) {
            time = arrivalTime;
        }

        if (i == 0) {
            responseTime[processIndex] = time - arrivalTime;
        } else {
            responseTime[processIndex] = time - arrivalTime + contextSwitchTime;
        }

        time += burstTime;
        finishTime[processIndex] = time;
        turnAroundTime[processIndex] = finishTime[processIndex] - arrivalTime;
        waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime;

        time += contextSwitchTime;
    }
}

void roundRobin(vector<Process>& processes, int contextSwitchTime, int quantum, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime) {
    queue<int> q;
    vector<int> remainingTime(processes.size()), startTime(processes.size(), -1);
    int time = 0;

    for (size_t i = 0; i < processes.size(); ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    size_t i = 0;
    while (!q.empty() || i < processes.size()) {
        while (i < processes.size() && processes[i].arrivalTime <= time) {
            q.push(i);
            i++;
        }

        if (!q.empty()) {
            int processIndex = q.front();
            q.pop();

            if (startTime[processIndex] == -1) {
                startTime[processIndex] = time;
                responseTime[processIndex] = time - processes[processIndex].arrivalTime;
            }

            int executionTime = min(quantum, remainingTime[processIndex]);
            time += executionTime;
            remainingTime[processIndex] -= executionTime;

            if (remainingTime[processIndex] > 0) {
                q.push(processIndex);
            } else {
                finishTime[processIndex] = time;
                turnAroundTime[processIndex] = finishTime[processIndex] - processes[processIndex].arrivalTime;
                waitingTime[processIndex] = turnAroundTime[processIndex] - processes[processIndex].burstTime;
            }

            time += contextSwitchTime;
        } else {
            time++;
        }
    }
}

void shortestJobFirst(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime || (a.burstTime == b.burstTime && a.arrivalTime < b.arrivalTime);
    });

    finishTime[0] = processes[0].arrivalTime + processes[0].burstTime;
    turnAroundTime[0] = finishTime[0] - processes[0].arrivalTime;
    waitingTime[0] = turnAroundTime[0] - processes[0].burstTime;
    responseTime[0] = waitingTime[0];

    for (size_t i = 1; i < processes.size(); ++i) {
        finishTime[i] = finishTime[i - 1] + processes[i].burstTime + contextSwitchTime;
        turnAroundTime[i] = finishTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnAroundTime[i] - processes[i].burstTime;
        responseTime[i] = waitingTime[i];
    }
}

void shortestRemainingTime(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime) {
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

            if (responseTime[current.index] == -1) {
                responseTime[current.index] = time - current.arrivalTime;
            }

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

void priorityScheduling(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime, vector<int>& responseTime) {
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

            if (responseTime[current.index] == -1) {
                responseTime[current.index] = time - current.arrivalTime;
            }

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
