#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

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

    // Add head to the request list for easier sorting
    requests.push_back(head);
    sort(requests.begin(), requests.end());

    int total_movement = 0;
    vector<int> sequence;
    int index = find(requests.begin(), requests.end(), head) - requests.begin();

    // Move toward higher value (right)
    for (int i = index; i < requests.size(); i++) {
        sequence.push_back(requests[i]);
    }

    // Then move to smaller values (left)
    for (int i = index - 1; i >= 0; i--) {
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
