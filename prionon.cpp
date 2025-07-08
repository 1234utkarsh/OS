#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority (higher number = higher priority)
    int completion; // Completion time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int response;   // Response time
    bool executed;  // Flag to check if process executed
};

void priorityScheduling(vector<Process>& processes) {
    int currentTime = 0;
    int totalIdleTime = 0;
    int completed = 0;
    int n = processes.size();
    
    cout << "\nGantt Chart:\n";
    
    while (completed != n) {
        int selected = -1;
        int highestPriority = INT_MIN;  // Changed to find maximum priority
        int earliestArrival = INT_MAX;
        
        // Find process with highest priority (largest number)
        for (int i = 0; i < n; i++) {
            if (!processes[i].executed && processes[i].arrival <= currentTime) {
                // If we find a higher priority process (larger number)
                if (processes[i].priority > highestPriority) {
                    selected = i;
                    highestPriority = processes[i].priority;
                    earliestArrival = processes[i].arrival;
                }
                // If priority equals current highest, pick earliest arrival
                else if (processes[i].priority == highestPriority && 
                         processes[i].arrival < earliestArrival) {
                    selected = i;
                    earliestArrival = processes[i].arrival;
                }
            }
        }
        
        // If no process found, CPU is idle
        if (selected == -1) {
            // Find next arriving process
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!processes[i].executed && processes[i].arrival < nextArrival) {
                    nextArrival = processes[i].arrival;
                }
            }
            
            if (nextArrival == INT_MAX) break; // No more processes
            
            cout << "| IDLE (" << currentTime << "-" << nextArrival << ") ";
            totalIdleTime += nextArrival - currentTime;
            currentTime = nextArrival;
            continue;
        }
        
        // Execute the selected process (non-preemptive)
        processes[selected].response = currentTime - processes[selected].arrival;
        cout << "| P" << processes[selected].pid << " (" << currentTime << "-" 
             << currentTime + processes[selected].burst << ") ";
        
        currentTime += processes[selected].burst;
        processes[selected].completion = currentTime;
        processes[selected].turnaround = processes[selected].completion - processes[selected].arrival;
        processes[selected].waiting = processes[selected].turnaround - processes[selected].burst;
        processes[selected].executed = true;
        completed++;
    }
    
    cout << "|\n\nTotal CPU idle time: " << totalIdleTime << endl;
}

void printResults(vector<Process>& processes) {
    int totalWaiting = 0, totalTurnaround = 0, totalResponse = 0;
    int n = processes.size();
    
    cout << "\nPID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\tResponse\n";
    for (auto& p : processes) {
        totalWaiting += p.waiting;
        totalTurnaround += p.turnaround;
        totalResponse += p.response;
        
        cout << p.pid << "\t"
             << p.arrival << "\t"
             << p.burst << "\t"
             << p.priority << "\t\t"
             << p.completion << "\t\t"
             << p.waiting << "\t"
             << p.turnaround << "\t\t"
             << p.response << "\n";
    }
    
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (float)totalWaiting / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaround / n << endl;
    cout << "Average Response Time: " << (float)totalResponse / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time and priority for process " << i + 1 << " (higher number = higher priority): ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
        processes[i].pid = i + 1;
        processes[i].executed = false;
    }
    
    priorityScheduling(processes);
    printResults(processes);
    
    return 0;
}