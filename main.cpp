#include "task.hpp"
#include <iostream>

void displayMenu() {
    std::cout << "Task Manager Menu" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Delete Task" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    TaskList taskList; // Create an instance of TaskList
    const std::string filename = "tasks.csv";

    taskList.loadFromFile(filename);

    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 1) { //infinite loop until a condition is picked that induces a break --> need to fix

            // Add a task
            std::cin.ignore(); // Ignore newline character from previous input
            std::string description;
            int priority;

            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter task priority (1-5): ";
            std::cin >> priority;

            taskList.addTask(description, priority);

        } else if (choice == 2) {
            // View tasks
            taskList.viewTasks();

        } else if (choice == 3) {
            std::cin.ignore();  //Need this to clear new line character
            std::string description;
            std::cout << "Enter task description to delete: ";
            std::getline(std::cin, description);
            taskList.deleteTask(description);

        } else if (choice == 4) {
            taskList.saveToFile(filename); // Save tasks at exit
            std::cout << "Exiting Task Manager. Goodbye!" << std::endl;
            break;

        } else {
            std::cout << "Invalid option. Please try again." << std::endl; //Handle invalid input. 
        }
    }

    return 0;
}
