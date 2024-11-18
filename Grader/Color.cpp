#include <iostream>
#include "Color.h"
using std::cout;
using std::string;

/**************************************************************************************
* color(string selection)
*   This will take a string an see if there is an available color code for it, then
* it changes the text to that color
***************************************************************************************/
void color(const string& selection) {
    if (selection == "reset") {
        cout << "\033[0m"; // Reset to default  
    }
    else if (selection == "white") {
        cout << "\033[38;2;255;255;255m"; // White  
    }
    else if (selection == "orange") {
        cout << "\033[38;2;255;165;0m"; // Orange  
    }
    else if (selection == "magenta") {
        cout << "\033[38;2;255;0;255m"; // Magenta  
    }
    else if (selection == "light blue") {
        cout << "\033[38;2;173;216;255m"; // Light Blue  
    }
    else if (selection == "yellow") {
        cout << "\033[38;2;255;255;0m"; // Yellow  
    }
    else if (selection == "lime") {
        cout << "\033[38;2;0;255;0m"; // Lime  
    }
    else if (selection == "pink") {
        cout << "\033[38;2;255;192;203m"; // Pink  
    }
    else if (selection == "gray") {
        cout << "\033[38;2;128;128;128m"; // Gray  
    }
    else if (selection == "light gray") {
        cout << "\033[38;2;211;211;211m"; // Light Gray  
    }
    else if (selection == "cyan") {
        cout << "\033[38;2;0;255;255m"; // Cyan  
    }
    else if (selection == "purple") {
        cout << "\033[38;2;128;0;128m"; // Purple  
    }
    else if (selection == "blue") {
        cout << "\033[38;2;0;0;255m"; // Blue  
    }
    else if (selection == "brown") {
        cout << "\033[38;2;165;42;42m"; // Brown  
    }
    else if (selection == "green") {
        cout << "\033[38;2;0;255;0m"; // Green  
    }
    else if (selection == "red") {
        cout << "\033[38;2;255;0;0m"; // Red  
    }
    else if (selection == "black") {
        cout << "\033[38;2;0;0;0m"; // Black  
    }
    else {
        std::cerr << "Color not recognized!" << std::endl; // Error handling  
    }
}

/**************************************************************************************
* color(int r, int g, int b)
*   This is an overloaded function that will change the color of the text based on
* 3 passed int values that represent RGB values, allowing me to make any color I want
***************************************************************************************/
void color(int r, int g, int b) {
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
}