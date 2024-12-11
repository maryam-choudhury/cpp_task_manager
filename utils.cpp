// Update 12/8: Added a new menu option to show task recommendations based on urgency and priority.
#include <iostream>
#include <string>
#include "utils.hpp"

void displayMenu() {
    std::cout << "\n" << std::string(40, '=') << std::endl; // Top border
    std::cout << "|           TASK MANAGER MENU          |"<< std::endl;
    std::cout << "| 1. Add Task                          |" << std::endl;
    std::cout << "| 2. View Tasks                        |" << std::endl;
    std::cout << "| 3. Delete Task                       |" << std::endl;
    std::cout << "| 4. Sort Tasks (Ascending)            |"<< std::endl;
    std::cout << "| 5. Sort Tasks (Descending)           |"  << std::endl;
    std::cout << "| 6. Save Tasks                        |"<< std::endl; // New menu option for saving tasks
    std::cout << "| 7. Search Tasks                      |"  << std::endl; // Update 12/8: New option for searching tasks
    std::cout << "| 8. Recommendations for Today         |" << std::endl; // Update 12/8: Added option for recommendations
    std::cout << "| 9. Exit                              |"<< std::endl;       // Updated option number for exiting
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Please choose an option: ";
}

// Success and error messages
void displaySuccessMessage(const std::string& message) {
    std::cout << "\n✅ " << message << "\n";
}

void displayErrorMessage(const std::string& message) {
    std::cout << "\n❌ " << message << "\n";
}