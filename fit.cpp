#include <iostream>
#include <vector>
#include <string>

// Represents a single block of memory
struct MemoryBlock {
    int id;
    int size;
    bool is_allocated;
    int process_id; // Which process is using this block (-1 if free)
};

// Represents a process requesting memory
struct Process {
    int id;
    int size;
};

// Helper function to print the current state of memory
void printMemoryLayout(const std::string& title, const std::vector<MemoryBlock>& memory) {
    std::cout << "--- " << title << " Memory Layout ---\n";
    std::cout << "Block ID\tSize\t\tAllocated\tProcess ID\n";
    std::cout << "----------------------------------------------------\n";
    for (const auto& block : memory) {
        std::cout << block.id << "\t\t" << block.size << "K\t\t"
                  << (block.is_allocated ? "Yes" : "No") << "\t\t"
                  << (block.is_allocated ? std::to_string(block.process_id) : "N/A") << "\n";
    }
    std::cout << "\n";
}

// --- Allocation Algorithms ---

// 1. First-Fit Algorithm
void firstFit(std::vector<MemoryBlock>& memory, const std::vector<Process>& processes) {
    for (const auto& process : processes) {
        bool allocated = false;
        for (auto& block : memory) {
            if (!block.is_allocated && block.size >= process.size) {
                block.is_allocated = true;
                block.process_id = process.id;
                allocated = true;
                std::cout << "Process " << process.id << " (" << process.size << "K) allocated to Block " << block.id << ".\n";
                break; // Go to the next process once allocated
            }
        }
        if (!allocated) {
            std::cout << "Process " << process.id << " (" << process.size << "K) could not be allocated.\n";
        }
    }
}

// 2. Best-Fit Algorithm
void bestFit(std::vector<MemoryBlock>& memory, const std::vector<Process>& processes) {
    for (const auto& process : processes) {
        int best_block_index = -1;
        
        // Find the smallest block that fits
        for (int i = 0; i < memory.size(); ++i) {
            if (!memory[i].is_allocated && memory[i].size >= process.size) {
                if (best_block_index == -1) {
                    best_block_index = i;
                } else if (memory[i].size < memory[best_block_index].size) {
                    best_block_index = i;
                }
            }
        }

        if (best_block_index != -1) {
            memory[best_block_index].is_allocated = true;
            memory[best_block_index].process_id = process.id;
            std::cout << "Process " << process.id << " (" << process.size << "K) allocated to Block " << memory[best_block_index].id << ".\n";
        } else {
            std::cout << "Process " << process.id << " (" << process.size << "K) could not be allocated.\n";
        }
    }
}

// 3. Worst-Fit Algorithm
void worstFit(std::vector<MemoryBlock>& memory, const std::vector<Process>& processes) {
    for (const auto& process : processes) {
        int worst_block_index = -1;
        
        // Find the largest block that fits
        for (int i = 0; i < memory.size(); ++i) {
            if (!memory[i].is_allocated && memory[i].size >= process.size) {
                if (worst_block_index == -1) {
                    worst_block_index = i;
                } else if (memory[i].size > memory[worst_block_index].size) {
                    worst_block_index = i;
                }
            }
        }

        if (worst_block_index != -1) {
            memory[worst_block_index].is_allocated = true;
            memory[worst_block_index].process_id = process.id;
            std::cout << "Process " << process.id << " (" << process.size << "K) allocated to Block " << memory[worst_block_index].id << ".\n";
        } else {
            std::cout << "Process " << process.id << " (" << process.size << "K) could not be allocated.\n";
        }
    }
}


int main() {
    // --- Initial State ---
    std::vector<MemoryBlock> initial_memory = {
        {1, 100, false, -1},
        {2, 500, false, -1},
        {3, 200, false, -1},
        {4, 300, false, -1},
        {5, 600, false, -1}
    };

    std::vector<Process> processes = {
        {1, 212},
        {2, 417},
        {3, 112},
        {4, 426}
    };

    std::cout << "========================================\n";
    std::cout << "    Contiguous Memory Allocation         \n";
    std::cout << "========================================\n\n";
    
    printMemoryLayout("Initial", initial_memory);

    // --- First-Fit Simulation ---
    std::cout << "\n--- Running First-Fit ---\n";
    std::vector<MemoryBlock> memory_ff = initial_memory;
    firstFit(memory_ff, processes);
    printMemoryLayout("First-Fit Final", memory_ff);

    // --- Best-Fit Simulation ---
    std::cout << "\n--- Running Best-Fit ---\n";
    std::vector<MemoryBlock> memory_bf = initial_memory;
    bestFit(memory_bf, processes);
    printMemoryLayout("Best-Fit Final", memory_bf);

    // --- Worst-Fit Simulation ---
    std::cout << "\n--- Running Worst-Fit ---\n";
    std::vector<MemoryBlock> memory_wf = initial_memory;
    worstFit(memory_wf, processes);
    printMemoryLayout("Worst-Fit Final", memory_wf);

    return 0;
}
