// This file will contain implementation of TaskList function

#include "task.hpp"
#include <iostream> // Needed for input and output
#include <fstream> // Needed for file operations
#include <sstream> // Needed for string parsing 

void TaskList::addTask(const std::string& description, int priority) {
    // Create a new task with the given description and priority
    Task* newTask = new Task(description, priority);

    
    newTask->next = head; //setting next Pointer of newTask to point at head, effectively making it the beginnning of the list
    head = newTask; //make newTask new head

    std::cout << "Task added: " << description << " with priority " << priority << std::endl;
}

void TaskList::viewTasks() const {
    // Start from the head of the list
    Task* current = head;

    if (!current) {
        std::cout << "No tasks to display." << std::endl;
        return;
    }

    // Iterate through the list and print each task
    // << is the insertion operator and lets variables be printed
    std::cout << "Current tasks:" << std::endl;
    while (current) {
        std::cout << "Description: " << current->description << ", Priority: " << current->priority << std::endl; //x->y so we can access what current is pointing to 
        current = current->next;
    }
}
// Save tasks to a CSV file
void TaskList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename); // Open file for writing

    if (!outFile) { //if opened successfully 
        std::cerr << "Error opening file for saving." << std::endl;
        return;  //if can't open file, exit function
    }

    Task* current = head;
    while (current) {
        // Write each task's description and priority, separated by a comma
        outFile << current->description << "," << current->priority << std::endl; //outFile << current->name << "," << current->value << std::endl;
        current = current->next; //current now points to next value
    }

    outFile.close();
    std::cout << "Tasks saved to " << filename << std::endl; //save confirmation
}
// Load tasks from a CSV file
void TaskList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename); // Open file for reading

    if (!inFile) {
        std::cerr << "Error opening file for loading." << std::endl; //when file cant't be loaded
        return;
    }

    std::string description;
    int priority;
    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line); // Parse each line
        std::getline(iss, description, ','); // Get description up to comma
        iss >> priority; // Get priority as an integer

        addTask(description, priority); // Add each task to the list
    }

    inFile.close(); //close file after reading all tasks
    std::cout << "Tasks loaded from " << filename << std::endl;
}

void TaskList::deleteTask(const std::string& description) {
    Task* current = head;
    Task* previous = nullptr;

    while (current) {
        if (current->description == description) { // Task found
            if (previous) { // 'previous' pointer will keep track of the node before 'current' pointer
                previous->next = current->next; // Remove current from the list
            } else {
                head = current->next; // Update head if deleting first node
            }
            delete current; // Deallocate memory (avoid memory leaks)
            std::cout << "Task deleted: " << description << std::endl;
            return;
        }
        //updating pointers to move forward
        previous = current;
        current = current->next;
    }
    std::cout << "Task not found: " << description << std::endl;
}
void TaskList::sortTasks(bool ascending) {
    if (!head || !head->next) {
        // If the list is empty or has only one task, no sorting is required
        return;
    }

    bool swapped; // Flag to check if any swaps were made during any iteration
    do {
        swapped = false;
        Task* current = head;
        Task* prev = nullptr;

        while (current && current->next) {
            Task* next = current->next;

            // Determines if the tasks need to be swapped based on 'ascending' flag
            bool shouldSwap = ascending ? (current->priority > next->priority) : (current->priority < next->priority);

            if (shouldSwap) {
                // Swap nodes
                if (prev) {
                    prev->next = next;
                } else {
                    head = next; // Update head if you are swapping the first two nodes
                }

                current->next = next->next;
                next->next = current;
                swapped = true;
            }

            prev = shouldSwap ? next : current; // Update prev only if no swap occured!
            current = current->next;
        }
    } while (swapped);
}
