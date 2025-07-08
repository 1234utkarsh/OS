#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, head, disk_size;

    cout << "Enter number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the request sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter total number of cylinders (disk size): ";
    cin >> disk_size;

    // Add head, and cylinder boundaries (0 and disk_size-1)
    requests.push_back(head);
    requests.push_back(0);
    requests.push_back(disk_size - 1);
    sort(requests.begin(), requests.end());

    int total_movement = 0;
    vector<int> sequence;

    // Find position of head in sorted list
    int index = find(requests.begin(), requests.end(), head) - requests.begin();

    // First, service requests to the right of head
    for (int i = index; i < requests.size(); i++) {
        sequence.push_back(requests[i]);
    }

    // Jump to beginning (circular)
    for (int i = 0; i < index; i++) {
        sequence.push_back(requests[i]);
    }

    cout << "\nOrder of execution: ";
    for (int i = 0; i < sequence.size(); i++) {
        if (i == 0) {
            cout << sequence[i];
        } else {
            total_movement += abs(sequence[i] - sequence[i - 1]);
            cout << " -> " << sequence[i];
        }
    }

    cout << "\n\nTotal Head Movement = " << total_movement << " cylinders\n";

    return 0;
}
