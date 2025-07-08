#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    int capacity;
    cout << "Enter number of frames: ";
    cin >> capacity;

    cout << "Enter the page reference string (space-separated, end with -1): ";
    vector<int> pages;
    int x;
    while (cin >> x && x != -1) {
        pages.push_back(x);
    }

    unordered_set<int> memory;
    queue<int> order;
    int page_hit = 0, page_fault = 0;

    for (int page : pages) {
        // Page Hit
        if (memory.find(page) != memory.end()) {
            page_hit++;
        } 
        // Page Fault
        else {
            page_fault++;

            if (memory.size() == capacity) {
                int oldest = order.front();
                order.pop();
                memory.erase(oldest);
            }

            memory.insert(page);
            order.push(page);
        }
    }

    cout << "\nTotal Page Hits  = " << page_hit << endl;
    cout << "Total Page Faults = " << page_fault << endl;

    return 0;
}
