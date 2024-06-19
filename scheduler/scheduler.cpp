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

// Shortest Job First (SJF)
void shortestJobFirst(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int time = 0;
    size_t i = 0;
    while (i < processes.size() || !pq.empty()) {
        while (i < processes.size() && processes[i].arrivalTime <= time) {
            pq.push(make_pair(processes[i].burstTime, i));
            i++;
        }

        if (pq.empty()) {
            time++;
            continue;
        }

        int processIndex = pq.top().second;
        pq.pop();

        int burstTime = processes[processIndex].burstTime;
        time += burstTime;

        finishTime[processIndex] = time;
        turnAroundTime[processIndex] = finishTime[processIndex] - processes[processIndex].arrivalTime;
        waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime;

        time += contextSwitchTime;
    }
}

// Shortest Remaining Time First (SRTF)
void shortestRemainingTime(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> remainingTime(processes.size());
    for (size_t i = 0; i < processes.size(); ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    int time = 0;
    size_t completed = 0;
    while (completed < processes.size()) {
        for (size_t i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= time && remainingTime[i] > 0) {
                pq.push(make_pair(remainingTime[i], i));
            }
        }

        if (pq.empty()) {
            time++;
            continue;
        }

        int processIndex = pq.top().second;
        pq.pop();

        time++;
        remainingTime[processIndex]--;

        if (remainingTime[processIndex] == 0) {
            completed++;
            finishTime[processIndex] = time;
            turnAroundTime[processIndex] = finishTime[processIndex] - processes[processIndex].arrivalTime;
            waitingTime[processIndex] = turnAroundTime[processIndex] - processes[processIndex].burstTime;
        }
        while(!pq.empty()){
            pq.pop();
        }
        time += contextSwitchTime;
    }
}

// Priority Scheduling
void priorityScheduling(vector<Process>& processes, int contextSwitchTime, vector<int>& finishTime, vector<int>& turnAroundTime, vector<int>& waitingTime) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int time = 0;
    size_t i = 0;
    while (i < processes.size() || !pq.empty()) {
        while (i < processes.size() && processes[i].arrivalTime <= time) {
            pq.push(make_pair(processes[i].priority, i));
            i++;
        }

        if (pq.empty()) {
            time++;
            continue;
        }

        int processIndex = pq.top().second;
        pq.pop();

        int burstTime = processes[processIndex].burstTime;
        time += burstTime;

        finishTime[processIndex] = time;
        turnAroundTime[processIndex] = finishTime[processIndex] - processes[processIndex].arrivalTime;
        waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime;

        time += contextSwitchTime;
    }
}
