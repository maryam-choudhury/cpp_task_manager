#ifndef TASK_LIST_HPP
#define TASK_LIST_HPP

#include "task.hpp"  // Include Task class for TaskList

class TaskList {
private:
    std::vector<Task*> tasks;  // Store tasks in a vector

public:
    TaskList() = default;  // Constructor

    // Method declarations for TaskList
    void addTask(Task* task);
    void viewTasks() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void deleteTask(const std::string& description);
    void sortTasks(bool ascending);
    void searchTasks(const std::string& keyword) const;
    void showRecommendations() const;  // Recommendations for today
};

#endif  // TASK_LIST_HPP
