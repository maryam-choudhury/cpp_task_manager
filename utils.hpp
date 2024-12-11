// UTILS_HPP 
//Making this file bc I have an issue of including .cpp files in other .cpp files.
#ifndef UTILS_HPP
#define UTILS_HPP
//Above do not need to match file name, just have to be unique

#include <string>

// Function declarations (not definitions)
void displayMenu();
void displaySuccessMessage(const std::string& message);
void displayErrorMessage(const std::string& message);

#endif 
