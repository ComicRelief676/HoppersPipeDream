#pragma once
#include <string>
/*******************************************************
* Color.h
*	This class will change the color of the text output
* to the terminal
********************************************************/

// this will take a selection of preset colors
void color(const std::string& selection);

// this will take RGB values
void color(int r, int g, int b);
