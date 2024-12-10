//task.hpp
// This file will contain Task struc and TaskList class defs

//header guards. Avoid multiple copies of the same header file aka reefinition errors
#ifndef TASK_HPP 
#define TASK_HPP

#include <string>
#include <iostream>

class Task {
public:
    std::string description;
    int priority;

    Task(std::string desc, int prio) : description(desc), priority(prio) {}

    virtual void display() const {
        std::cout << description << " (Priority: " << priority << ")";
    }

    // Update Operator Overload: Overloading the is equal aka '==' operator for task comparison based on description and priority.
    bool operator==(const Task& other) const {
        return description == other.description && priority == other.priority;
    }

    // Update Operator Overload: Overloading the  less than aka '<' operator for task comparison based on priority.
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

    virtual ~Task() = default; // Ensure the base class is destructible (Remember to add Microsoft destructor page to your bibliogaphy!!!!)
};

class WorkTask : public Task {
private:
    std::string deadline; // attribute for work tasks

public:
    WorkTask(std::string desc, int prio, std::string dueDate)
        : Task(desc, prio), deadline(dueDate) {}

    // Update Display 12/8: Display work task with deadline
    void display() const override {
        std::cout << "[Work] " << description << " (Priority: " << priority
                  << ", Deadline: " << deadline << ")";
    }

    // Update Inheritance: Added a method specific to work tasks to get the deadline.
    std::string getDeadline() const { return deadline; }
};

class PersonalTask : public Task {
private:
    std::string reminderTime; // Specialized attribute for personal tasks

public:
    PersonalTask(std::string desc, int prio, std::string reminder)
        : Task(desc, prio), reminderTime(reminder) {}

    // Update Display 12/8: Displaying personal task with reminder time
    void display() const override {
        std::cout << "[Personal] " << description << " (Priority: " << priority
                  << ", Reminder: " << reminderTime << ")";
    }

    // Update Inheritance: Added a method specific to personal tasks for getting the reminder time.
    std::string getReminderTime() const { return reminderTime; }
};

#endif
