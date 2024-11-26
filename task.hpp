// This file will contain Task struc and TaskList class defs

//header guards. Avoid multiple copies of the same header file aka reefinition errors
#ifndef TASK_HPP 
#define TASK_HPP

#include <string>

struct Task{ //giving container, so using struct !class
    std:: string description; //task description
    int priority; //task priority level
    Task* next; // Pointer, next task in task linked list

    //member initializer link constructor syntax:
    // ClassName(int a, double b, std::string c) : member1(a), member2(b), member3(c) {}
    Task(const std::string& desc, int prio) : description(desc), priority(prio), next(nullptr) {}
};

class TaskList{
    private: //making the head private so it doesn't get mixed up with other heads
        Task* head; //Pointer to the head aka first task
    public:
        TaskList(): head(nullptr) {}
        void addTask(const std::string& description, int priority); //add new task
        void viewTasks() const; //const means member variables of this class can't be changed
        void saveToFile(const std::string& filename) const; // saves tasks to a file
        void sortTasks(bool ascending); // Sort tasks by priority (ascending if true, descending if false)
void loadFromFile(const std::string& filename);     // loads tasks from a file
void deleteTask(const std::string& description); // Delete task by description



};




#endif