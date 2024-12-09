// This file will contain implementation of TaskList function
#include "task.hpp"
#include <iostream> // Needed for input and output
#include <fstream> // Needed for file operations
#include <sstream> // Needed for string parsing 
#include <ctime>
#include <algorithm>

void TaskList::addTask(Task* task) {
    tasks.push_back(task);
}

void TaskList::viewTasks() const {
    for (const auto& task : tasks) {
        task->display();
        std::cout << std::endl;
    }
}

void TaskList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename); // Open file for writing

    if (!outFile) { // If the file cannot be opened
        std::cerr << "Error opening file for saving." << std::endl;
        return; // Exit the function if the file cannot be opened
    }

    for (const auto& task : tasks) {
        if (WorkTask* work = dynamic_cast<WorkTask*>(task)) {
            outFile << work->description << "," << work->priority << "," << work->getDeadline() << std::endl;
        } else if (PersonalTask* personal = dynamic_cast<PersonalTask*>(task)) {
            outFile << personal->description << "," << personal->priority << "," << personal->getReminderTime() << std::endl;
        }
    }

    outFile.close();
    std::cout << "Tasks saved to " << filename << std::endl;
}

void TaskList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename); // Open file for reading

    if (!inFile) {
        std::cerr << "Error opening file for loading." << std::endl; // When the file can't be opened
        return;
    }

    std::string description;
    int priority;
    std::string category, deadline, reminder;
    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line); // Parse each line
        std::getline(iss, description, ','); // Get description up to comma
        iss >> priority; // Get priority as an integer
        std::getline(iss, category, ','); // Get category (work/personal)
        if (category == "work") {
            std::getline(iss, deadline); // Get deadline
            addTask(new WorkTask(description, priority, deadline));
        } else if (category == "personal") {
            std::getline(iss, reminder); // Get reminder time
            addTask(new PersonalTask(description, priority, reminder));
        }
    }

    inFile.close(); // Close file after reading all tasks
    std::cout << "Tasks loaded from " << filename << std::endl;
}

void TaskList::deleteTask(const std::string& description) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&description](Task* task) {
        return task->description == description;
    });

    if (it != tasks.end()) {
        delete *it;
        tasks.erase(it);
        std::cout << "Task deleted: " << description << std::endl;
    } else {
        std::cout << "Task not found: " << description << std::endl;
    }
}

void TaskList::sortTasks(bool ascending) {
    std::sort(tasks.begin(), tasks.end(), [ascending](Task* a, Task* b) {
        return ascending ? (*a < *b) : (*b < *a); // Use overloaded '<' operator for sorting
    });
}

void TaskList::searchTasks(const std::string& keyword) const {
    bool found = false;
    for (const auto& task : tasks) {
        if (task->description.find(keyword) != std::string::npos) {
            task->display();
            std::cout << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No tasks found with the keyword '" << keyword << "'." << std::endl;
    }
}

// Update 12/8: Show recommendations based on urgency and priority
void TaskList::showRecommendations() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::cout << "\nRecommendations for Today (" << 1900 + ltm->tm_year << "-" 
              << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "):\n";

    // Sort tasks first by urgency (deadline) and priority
    for (const auto& task : tasks) {
        if (auto* workTask = dynamic_cast<WorkTask*>(task)) {
            if (workTask->getDeadline() < std::to_string(1900 + ltm->tm_year) + "-" 
                + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday)) {
                std::cout << "Urgent: ";
                workTask->display();
                std::cout << std::endl;
            }
        }
    }
}
