#include "task.hpp"
#include <iostream>

void displayMenu() {
    std::cout << "Task Manager Menu" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Delete Task" << std::endl;
    std::cout << "4. Sort Tasks (Ascending)" << std::endl;
    std::cout << "5. Sort Tasks (Descending)" << std::endl;
    std::cout << "6. Save Tasks" << std::endl; // New menu option for saving tasks
    std::cout << "7. Exit" << std::endl;       // Updated option number for exiting
    std::cout << "Choose an option: ";
}

int main() {
    TaskList taskList; // Create an instance of TaskList
    const std::string filename = "tasks.csv";

    taskList.loadFromFile(filename); // Loading tasks from file at the start 
                                    //--> How can I add a condition to prevent error message from popping up when prgm is 1st run?

    int choice; // Variable to store the menu choice

    while (true) {
        displayMenu();
        std::cin >> choice;

        // Clearing the input buffer to avoid leftover characters interfering with further input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            // Add a task
            std::string description;
            int priority;

            // Input validation for description
            do {
                std::cout << "Enter task description: ";
                std::getline(std::cin, description); // Use std::getline to capture multi-word descriptions
                if (description.empty()) { 
                    std::cout << "Description cannot be empty. Please try again." << std::endl; 
                }
            } while (description.empty()); // Ensure the user provides a valid non-empty description

            // Input validation for priority
            do { 
                std::cout << "Enter task priority (1-5): ";
                std::cin >> priority;

                // Clear the input buffer after reading priority
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (priority < 1 || priority > 5) { 
                    std::cout << "Invalid priority. Enter a value between 1 and 5." << std::endl; 
                }
            } while (priority < 1 || priority > 5); // Checks that priority is within the valid range

            taskList.addTask(description, priority); // Add the task to the linked list

        } else if (choice == 2) {
            // View tasks
            taskList.viewTasks(); // Display all tasks in the linked list

        } else if (choice == 3) {
            // Delete a task
            std::string description;
            std::cout << "Enter task description to delete: ";
            std::getline(std::cin, description); // Use std::getline to capture multi-word descriptions
            taskList.deleteTask(description); // Attempt to delete the task

        } else if (choice == 4) {
            // Sort tasks in ascending order
            taskList.sortTasks(true); // Call sortTasks with ascending=true
            std::cout << "Tasks sorted in ascending order." << std::endl;

        } else if (choice == 5) {
            // Sort tasks in descending order
            taskList.sortTasks(false); // Call sortTasks w/ ascending=false
            std::cout << "Tasks sorted in descending order." << std::endl;

        } else if (choice == 6) {
            // Save tasks to file
            taskList.saveToFile(filename); // Writing all tasks to the file
            std::cout << "Tasks saved to " << filename << std::endl;

        } else if (choice == 7) {
            // Exit the program
            taskList.saveToFile(filename); // Saving tasks to the file before exiting
            std::cout << "Exiting Task Manager. Goodbye!" << std::endl;
            break; // Exit the infinite loop and terminate the program

        } else {
            // Handle invalid menu input
            std::cout << "Invalid option. Please try again." << std::endl; //Would a more generalized error message be less clear?
            //Condition to think aout: user has never run the program so there is no tasks.csv
        }
    }

    return 0; //prgm succesfully terminated 
}
