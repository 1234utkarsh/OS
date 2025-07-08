#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void printTable(const vector<Process>& processes, const vector<int>& completionTime, const vector<int>& turnaroundTime, const vector<int>& waitingTime) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << completionTime[i] << "\t\t" << turnaroundTime[i] << "\t\t\t" << waitingTime[i] << endl;
    }
}

void roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    vector<int> completionTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    queue<int> readyQueue;
    vector<bool> inQueue(n, false);

    int currentTime = 0;
    int completed = 0;
    int currentProcessIndex = 0;

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    for(auto& p : processes) {
        p.remainingTime = p.burstTime;
    }

    while (completed < n) {
        while (currentProcessIndex < n && processes[currentProcessIndex].arrivalTime <= currentTime) {
            if (!inQueue[currentProcessIndex]) {
                readyQueue.push(currentProcessIndex);
                inQueue[currentProcessIndex] = true;
            }
            currentProcessIndex++;
        }

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        int processIndex = readyQueue.front();
        readyQueue.pop();

        int executeTime = min(quantum, processes[processIndex].remainingTime);
        processes[processIndex].remainingTime -= executeTime;
        currentTime += executeTime;

        while (currentProcessIndex < n && processes[currentProcessIndex].arrivalTime <= currentTime) {
            if (!inQueue[currentProcessIndex]) {
                readyQueue.push(currentProcessIndex);
                inQueue[currentProcessIndex] = true;
            }
            currentProcessIndex++;
        }

        if (processes[processIndex].remainingTime > 0) {
            readyQueue.push(processIndex);
        } else {
            completionTime[processIndex] = currentTime;
            turnaroundTime[processIndex] = completionTime[processIndex] - processes[processIndex].arrivalTime;
            waitingTime[processIndex] = turnaroundTime[processIndex] - processes[processIndex].burstTime;
            completed++;
            inQueue[processIndex] = false; 
        }
    }

    printTable(processes, completionTime, turnaroundTime, waitingTime);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    int quantum;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    roundRobin(processes, quantum);

    return 0;
}
