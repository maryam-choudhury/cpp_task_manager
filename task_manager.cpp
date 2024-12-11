//task_manager.cpp
#include "task.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <ctime>
#include "task_list.hpp"
#include "utils.hpp"


int main() {
    TaskList taskList; // Create an instance of TaskList
    const std::string filename = "tasks.csv";

    taskList.loadFromFile(filename); // Loading tasks from file at the start

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
            std::string category;

            // Input validation for description
            do {
                std::cout << "Enter task description: ";
                std::getline(std::cin, description); // Use std::getline to capture multi-word descriptions
                if (description.empty()) { 
                    std::cout << "Description cannot be empty. Please try again." << std::endl; 
                }
            } while (description.empty()); // User has to provide a valid non-empty description --> test case neccessary 

            // Input validation for priority
            do { 
                std::cout << "Enter task priority (1-5): ";
                std::cin >> priority;

                // Clear the input buffer after reading priority
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (priority < 1 || priority > 5) { 
                    std::cout << "Invalid priority. Enter a value between 1 and 5." << std::endl; 
                }
            } while (priority < 1 || priority > 5); // Checking that priority is within the valid range

            // Input for task category
            std::cout << "Enter task category (work/personal): ";
            std::getline(std::cin, category); // Allow multi-word category names
            if (category == "work") {
                std::string deadline;
                std::cout << "Enter the work task deadline (YYYY-MM-DD): ";
                std::getline(std::cin, deadline);
                taskList.addTask(new WorkTask(description, priority, deadline)); // Update Inheritance: Created a work task
            } else if (category == "personal") {
                std::string reminder;
                std::cout << "Enter the personal task reminder time (HH:MM): ";
                std::getline(std::cin, reminder);
                taskList.addTask(new PersonalTask(description, priority, reminder)); // Update Inheritance: Created a personal task
            } else {
                std::cout << "Invalid category." << std::endl;
            }

        } else if (choice == 2) {
            // View tasks
            taskList.viewTasks(); // Display all tasks in the linked list

        } else if (choice == 3) {
            // Delete a task
            std::string description;
            std::cout << "Enter task description to delete: ";
            std::getline(std::cin, description); // Use std::getline to capture multi-word descriptions (syntax error???)
            taskList.deleteTask(description); // Attempt to delete the task
            displaySuccessMessage("Task successfully deleted!"); //send to success message

        } else if (choice == 4) {
            // Sort tasks in ascending order
            taskList.sortTasks(true); // Call sortTasks with ascending=true
            std::cout << "Tasks sorted in ascending order." << std::endl;

        } else if (choice == 5) {
            // Sort tasks in descending order
            taskList.sortTasks(false); // Call sortTasks with ascending=false
            std::cout << "Tasks sorted in descending order." << std::endl;

        } else if (choice == 6) {
            // Save tasks to file
            taskList.saveToFile(filename); // Writing all tasks to the file
            std::cout << "Tasks saved to " << filename << std::endl;

        } else if (choice == 7) {
            // Search for tasks
            std::string keyword;
            std::cout << "Enter keyword to search: ";
            std::getline(std::cin, keyword); // Use std::getline to allow multi-word search terms
            taskList.searchTasks(keyword); // Update 12/8: Call searchTasks with the entered keyword

        } else if (choice == 8) {
            // Recommendations for given day based on urgency and priority
            taskList.showRecommendations(); // Update 12/8: Added recommendations based on task urgency
        } else if (choice == 9) {
            // Exit
            taskList.saveToFile(filename); // Saving tasks to the file before exiting
            std::cout << "Exiting Task Manager. Goodbye!" << std::endl;
            displaySuccessMessage("Tasks succesfully saved to file. Now exiting Task Manager. Goodbye!");
            break; // bad choice?

        } else {
            // Handle invalid menu input
            displayErrorMessage("Invalid option. Please try again.");
        }
    }

    return 0; //exit!
}
