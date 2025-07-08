#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to find the page to replace
int findOptimalPageToReplace(vector<int> &pages, unordered_set<int> &memory, int currentIndex) {
    int farthestIndex = -1;
    int pageToReplace = -1;

    for (int page : memory) {
        int nextUse = -1;
        for (int i = currentIndex + 1; i < pages.size(); i++) {
            if (pages[i] == page) {
                nextUse = i;
                break;
            }
        }

        // If not used again, replace this page
        if (nextUse == -1) {
            return page;
        }

        // Track farthest use
        if (nextUse > farthestIndex) {
            farthestIndex = nextUse;
            pageToReplace = page;
        }
    }

    return pageToReplace;
}

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
    int page_hit = 0, page_fault = 0;

    for (int i = 0; i < pages.size(); i++) {
        int current_page = pages[i];

        // Page Hit
        if (memory.find(current_page) != memory.end()) {
            page_hit++;
        } 
        // Page Fault
        else {
            page_fault++;

            if (memory.size() == capacity) {
                int to_replace = findOptimalPageToReplace(pages, memory, i);
                memory.erase(to_replace);
            }

            memory.insert(current_page);
        }
    }

    cout << "\nTotal Page Hits  = " << page_hit << endl;
    cout << "Total Page Faults = " << page_fault << endl;

    return 0;
}
