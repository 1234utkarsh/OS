#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int completion; // Completion time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int response;   // Response time (first execution start - arrival)
};

void calculateTimes(vector<Process>& processes) {
    int currentTime = 0;
    int totalIdleTime = 0;
    
    for (auto& p : processes) {
        // If the process arrives after current time, CPU is idle
        if (p.arrival > currentTime) {
            totalIdleTime += p.arrival - currentTime;
            cout << "CPU idle from " << currentTime << " to " << p.arrival << endl;
            currentTime = p.arrival;
        }
        
        // Set response time (first time the process gets CPU)
        p.response = currentTime - p.arrival;
        
        // Start execution
        p.completion = currentTime + p.burst;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
        
        currentTime = p.completion;
    }
    
    cout << "\nTotal CPU idle time: " << totalIdleTime << endl;
}

void printResults(const vector<Process>& processes) {
    int totalWaiting = 0, totalTurnaround = 0, totalResponse = 0;
    int n = processes.size();
    
    cout << "\nPID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\tResponse\n";
    for (const auto& p : processes) {
        totalWaiting += p.waiting;
        totalTurnaround += p.turnaround;
        totalResponse += p.response;
        
        cout << p.pid << "\t"
             << p.arrival << "\t"
             << p.burst << "\t"
             << p.completion << "\t\t"
             << p.waiting << "\t"
             << p.turnaround << "\t\t"
             << p.response << "\n";
    }
    
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaiting / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaround / n << endl;
    cout << "Average Response Time: " << (float)totalResponse / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].pid = i + 1;
    }
    
    // Sort processes by arrival time (FCFS)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });
    
    calculateTimes(processes);
    printResults(processes);
    
    return 0;
}