#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
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
    unordered_map<int, int> recent_use;  // page -> last used index
    int page_hit = 0, page_fault = 0;

    for (int i = 0; i < pages.size(); i++) {
        int current_page = pages[i];

        // Page Hit
        if (memory.find(current_page) != memory.end()) {
            page_hit++;
        } 
        // Page Miss
        else {
            page_fault++;

            // If memory is full, remove the MRU page
            if (memory.size() == capacity) {
                int mru_page = -1, max_index = -1;
                for (int page : memory) {
                    if (recent_use[page] > max_index) {
                        max_index = recent_use[page];
                        mru_page = page;
                    }
                }
                memory.erase(mru_page);
            }

            memory.insert(current_page);
        }

        // Update usage timestamp
        recent_use[current_page] = i;
    }

    cout << "\nTotal Page Hits  = " << page_hit << endl;
    cout << "Total Page Faults = " << page_fault << endl;

    return 0;
}
