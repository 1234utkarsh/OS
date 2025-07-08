#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Total burst time
    int remaining;   // Remaining burst time
    int priority;    // Priority (higher number = higher priority)
    int completion;  // Completion time
    int waiting;     // Waiting time
    int turnaround;  // Turnaround time
    int response;    // Response time (-1 means not responded yet)
    bool in_queue;   // Whether process is in ready queue
};

void preemptivePriority(vector<Process>& processes) {
    int currentTime = 0;
    int totalIdleTime = 0;
    int completed = 0;
    int n = processes.size();
    
    // Initialize process states
    for (auto& p : processes) {
        p.remaining = p.burst;
        p.response = -1;
        p.in_queue = false;
    }
    
    cout << "\nGantt Chart:\n";
    cout << "|";
    
    while (completed != n) {
        // Check for newly arrived processes
        for (auto& p : processes) {
            if (p.arrival == currentTime) {
                p.in_queue = true;
            }
        }
        
        // Find process with highest priority (largest number) and not completed
        int selected = -1;
        int highestPriority = INT_MIN;
        int earliestArrival = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].in_queue && processes[i].remaining > 0) {
                // Select process with higher priority (larger number)
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
        
        // If no process available, CPU is idle
        if (selected == -1) {
            // Find next arriving process
            int nextArrival = INT_MAX;
            for (auto& p : processes) {
                if (p.remaining > 0 && p.arrival > currentTime && p.arrival < nextArrival) {
                    nextArrival = p.arrival;
                }
            }
            
            if (nextArrival == INT_MAX) {
                // No more processes coming
                currentTime++;
                continue;
            }
            
            cout << " IDLE (" << currentTime << "-" << nextArrival << ") |";
            totalIdleTime += nextArrival - currentTime;
            currentTime = nextArrival;
            continue;
        }
        
        // Mark response time if this is first execution
        if (processes[selected].response == -1) {
            processes[selected].response = currentTime - processes[selected].arrival;
        }
        
        // Execute the process for 1 unit of time (preemptive)
        cout << " P" << processes[selected].pid << " (" << currentTime << ") |";
        processes[selected].remaining--;
        currentTime++;
        
        // Check if process completed
        if (processes[selected].remaining == 0) {
            completed++;
            processes[selected].completion = currentTime;
            processes[selected].turnaround = processes[selected].completion - processes[selected].arrival;
            processes[selected].waiting = processes[selected].turnaround - processes[selected].burst;
            processes[selected].in_queue = false;
        }
    }
    
    cout << "\n\nTotal CPU idle time: " << totalIdleTime << endl;
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
        cout << "Enter arrival time, burst time and priority for process " << i + 1 
             << " (higher number = higher priority): ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
        processes[i].pid = i + 1;
    }
    
    preemptivePriority(processes);
    printResults(processes);
    
    return 0;
}