//task_list.cpp
// This file will contain implementation of TaskList function
#include "task.hpp"
#include "task_list.hpp"  // Include the header file where TaskList is declared
#include "utils.hpp" // 12/10 Update: Include utils for displaySuccessMessage and displayErrorMessage
#include <iostream> // Needed for input and output
#include <fstream> // Needed for file operations
#include <sstream> // Needed for string parsing 
#include <ctime>
#include <algorithm>

void TaskList::addTask(Task* task) {
    tasks.push_back(task);
}

void TaskList::viewTasks() const {
    
    if (tasks.empty()) {
        displayErrorMessage("No tasks to display.");
        return;
    }
    //pretty formatting
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "|            ALL TASKS                |" << std::endl;
    std::cout << std::string(40, '=') << std::endl;

    bool firstTask = true; // 12-10 Update: Check if it's the first task to avoid an extra line separator
    for (const auto& task : tasks) {
        if (!firstTask) {
            std::cout << std::string(40, '-') << std::endl; // Separator only between tasks
        }
        task->display();
        firstTask = false;
    }

    std::cout << "\n" << std::string(40, '=') << "\n";
}

void TaskList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename); // Open file for writing

    if (!outFile) { // If the file cannot be opened
        displayErrorMessage("Error opening file for saving.");
        return; // Exit the function if the file cannot be opened
    }

    for (const auto& task : tasks) {
        if (WorkTask* work = dynamic_cast<WorkTask*>(task)) {
            outFile << "work," << work->description << "," << work->priority << "," << work->getDeadline() << std::endl;
        } else if (PersonalTask* personal = dynamic_cast<PersonalTask*>(task)) {
            outFile << "personal," << personal->description << "," << personal->priority << "," << personal->getReminderTime() << std::endl;
        }
    }

    outFile.close();
    displaySuccessMessage("Tasks saved successfully to " + filename);
}

void TaskList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename); // Open file for reading

    if (!inFile) {
        std::cerr << "Error opening file for loading." << std::endl; // When the file can't be opened
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line); 
        std::string category, description, priorityStr, timeInfo;
        
        // Parse each field using getline (since CSV is comma-separated)
        std::getline(iss, category, ','); 
        std::getline(iss, description, ','); 
        std::getline(iss, priorityStr, ','); 
        std::getline(iss, timeInfo, ',');

        int priority = std::stoi(priorityStr); // Convert priority to an integer

        if (category == "work") {
            addTask(new WorkTask(description, priority, timeInfo)); // "timeInfo" holds the deadline
        } else if (category == "personal") {
            addTask(new PersonalTask(description, priority, timeInfo)); // "timeInfo" holds the reminder
        }
    }

    inFile.close(); // Close file after reading all tasks
    displaySuccessMessage("Tasks loaded from " + filename);
}

void TaskList::deleteTask(const std::string& description) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&description](Task* task) {
        return task->description == description;
    });

    if (it != tasks.end()) {
        delete *it;
        tasks.erase(it);
        displaySuccessMessage("Task successfully deleted: " + description);
    } else {
       displayErrorMessage("Task not found: " + description);
    }
}

void TaskList::sortTasks(bool ascending) {
    std::sort(tasks.begin(), tasks.end(), [ascending](Task* a, Task* b) {
        return ascending ? (*a < *b) : (*b < *a); // Use overloaded  greater than aka '<' operator for sorting
    });
}

void TaskList::searchTasks(const std::string& keyword) const {
    bool found = false;
    for (const auto& task : tasks) {
        if (task->description.find(keyword) != std::string::npos) {
            task->display();
            std::cout << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No tasks found with the keyword '" << keyword << "'!" << std::endl;
    }
}

// Update 12/8: Show recommendations based on urgency and priority 
//Update 12/10: Add logic for if there is nothing due today
void TaskList::showRecommendations() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    // Note that all refferences are in bibliography file (vector usage!)
    std::string todayDate = std::to_string(1900 + ltm->tm_year) + "-" 
                          + (ltm->tm_mon + 1 < 10 ? "0" : "") + std::to_string(ltm->tm_mon + 1) + "-" 
                          + (ltm->tm_mday < 10 ? "0" : "") + std::to_string(ltm->tm_mday);

    std::vector<WorkTask*> dueToday;
    std::vector<WorkTask*> futureTasks;
    std::string nextSoonestDeadline = "9999-12-31"; // Placeholder for "future" date as greatest possible

    // Step 1: Split tasks into "due today" and "future" tasks
    for (const auto& task : tasks) {
        if (auto* workTask = dynamic_cast<WorkTask*>(task)) {
            std::string deadline = workTask->getDeadline();
            if (deadline == todayDate) {
                dueToday.push_back(workTask); // Tasks due today
            } else if (deadline > todayDate) {
                futureTasks.push_back(workTask); // Future tasks
                if (deadline < nextSoonestDeadline) {
                    nextSoonestDeadline = deadline; // Update to soonest deadline
                }
            }
        }
    }

    // Step 2: Displaying tasks due today
    if (!dueToday.empty()) {
        std::cout << "\nUrgent! Tasks due today (" << todayDate << "):" << std::endl;
        for (const auto& task : dueToday) {
            task->display();
            std::cout << std::endl;
        }
    } 
    // Step 3: If no tasks are due today, will display tasks with the next soonest deadline
    else if (!futureTasks.empty()) {
        std::cout << "\nNo tasks are due today. Here are the tasks with the next soonest deadline (" 
                  << nextSoonestDeadline << ")!:" << std::endl;

        for (const auto& task : futureTasks) {
            if (task->getDeadline() == nextSoonestDeadline) {
                task->display();
                std::cout << std::endl;
            }
        }
    } 
    // Step 4: If no tasks loaded at all
    else {
        displayErrorMessage("No upcoming tasks to recommend.");
    }
}
