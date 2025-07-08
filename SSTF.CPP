#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

// Helper function to find the closest unvisited request
int findClosest(vector<int> &requests, vector<bool> &visited, int head) {
    int min_distance = INT_MAX;
    int index = -1;

    for (int i = 0; i < requests.size(); i++) {
        if (!visited[i]) {
            int distance = abs(requests[i] - head);
            if (distance < min_distance) {
                min_distance = distance;
                index = i;
            }
        }
    }

    return index;
}

int main() {
    int n, head;

    cout << "Enter number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the request sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    vector<bool> visited(n, false);
    int total_movement = 0;

    cout << "\nOrder of execution: " << head << " ";

    for (int i = 0; i < n; i++) {
        int index = findClosest(requests, visited, head);
        total_movement += abs(requests[index] - head);
        head = requests[index];
        visited[index] = true;

        cout << "-> " << head << " ";
    }

    cout << "\n\nTotal Head Movement = " << total_movement << " cylinders\n";

    return 0;
}
