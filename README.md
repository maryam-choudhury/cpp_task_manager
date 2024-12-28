# 🗂️ cpp_task_manager

## Introduction

This Task Manager program is an introductory project I developed while learning C++ during the Fall 2024 semester, and it’s designed to keep users organized while showcasing the power of object-oriented programming (OOP). As it was my first deep dive into C++, I made effort to put as many core characteristics of the language to use as possible. More on that below!

---

### Core Functionalities
1. **Add Tasks**: Creates tasks in two categories:
   - Work tasks with deadlines.
   - Personal tasks with reminder times.
2. **View Tasks**: Displays all tasks.
3. **Sort Tasks**: Organizes tasks by priority—ascending or priority-descending.
4. **Delete Tasks**: Removes tasks from the list based on their description.
5. **Search Tasks**: User can find tasks by keyword.
6. **Save and Load**: Saves tasks to a CSV file for persistence between sessions. 
7. **Recommendations**: Gives suggestions for tasks that need urgent attention today (or the next soonest deadline if nothing is due immediately).

---

### Technical Features
- **File I/O**: Implements file I/O to save and load tasks between user-sessions.
- **Polymorphism**: Utilizes base class pointers for handling different task types uniformly.
- **Operator Overloading**: Includes `==` and `<` operators for task comparison and sorting.
- **Encapsulation**: Protects sensitive attributes like deadlines and reminder times with getter methods.
- **Dynamic Memory Management**: Ensures efficient memory allocation and deallocation. For example, I declared a virtual ~Task() destructor in the Task class.

---

# Key Classes
1. **Task**: Base class for all tasks with core attributes like description and priority.
   - Methods: `display()`, `operator==`, `operator<`.

2. **WorkTask**: Inherits from `Task` and adds a deadline attribute.
   - Methods: `getDeadline()`, `display()`.

3. **PersonalTask**: Inherits from `Task` and adds a reminder time attribute.
   - Methods: `getReminderTime()`, `display()`.

4. **TaskList**: Manages all tasks and provides functionality for adding, viewing, sorting, deleting, and searching tasks.
   - Methods: `addTask()`, `viewTasks()`, `sortTasks()`, `deleteTask()`, `searchTasks()`, `saveToFile()`, `loadFromFile()`, `showRecommendations()`.

---

## How to Run

### Setup
1. Clone this repository.
2. Make sure you have a C++ compiler (for example, `g++` or `clang`).
3. Make sure all files (`task.hpp`, `task_list.hpp`, etc.) are in the same directory.

### Compilation
Run the following command in your terminal:
```bash
g++ task_list.cpp task_manager.cpp utils.cpp -o task_manager
