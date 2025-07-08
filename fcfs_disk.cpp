#include <iostream>
#include <vector>
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

    int total_movement = 0;
    cout << "\nOrder of execution: " << head << " ";

    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        cout << "-> " << head << " ";
    }

    cout << "\n\nTotal Head Movement = " << total_movement << " cylinders\n";

    return 0;
}
