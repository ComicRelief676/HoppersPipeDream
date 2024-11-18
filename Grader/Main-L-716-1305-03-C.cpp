#include <iostream>
#include <fstream> // allows us to pull from files
#include <string>
#include <vector>
#include "Color.h"

void displayFile(std::vector<std::string> fileToPrint);
void displayFile(std::vector<int> fileToPrint);

/********************************************************************
*	getFileName()
*	This function will ask the user to input a file name within
* the current directory and then returns that file name
********************************************************************/
std::string getFileName() {
	
	// option to display all files in current directory??

	std::string fileName;
	color("magenta");
	std::cout << "Input the name of the file you want to auto-grade (example: Item.txt):" << std::endl;
	color("reset");
	std::cin >> fileName;
	return fileName;
}

/********************************************************************
*	copyFile()
*	This function will take the name of a file in the current
* directory and then copies every line of that file to a vector, and
* returns the vector
********************************************************************/
std::vector<std::string> copyFile() {
	bool success = true;
	std::ifstream inputFile;
	do {
		// ask the user for the file path again
		std::string fileName = getFileName();
		inputFile.open(fileName);
		if (!inputFile) { // Check if the file opened successfully
			std::cerr << "Error opening file: " << fileName << std::endl;
			success = false;
		}
		else {
			success = true;
		}
	} while (!success);

	std::vector<std::string> lines; // Vector to store the lines
	std::string line;

	// Read each line from the file and store it in the vector
	while (std::getline(inputFile, line)) {
		lines.push_back(line);
	}

	inputFile.close(); // Close the file
	return lines;
}

/******************************************************************************
*	removeNesting(std::vector<std::string> input)
*	Removes all of the nesting in the file and returns the file all flush to
* the left
******************************************************************************/
std::vector<std::string> removeNesting(std::vector<std::string> input) {
	for (int i = 0; i < input.size(); i++) {
		if (input[i].length() > 1) {
			while (input[i].at(0) == ' ' || input[i].at(0) == '\t') {
				input[i] = input[i].substr(1, input[i].length());
			}
		}
	}
	return input;
}

/********************************************************************
*	functionChecker()
*	This will find all of the function definitions. It will check
* for parenthesis and an open brack '{' after making sure the line
* is not an if, while, for, or else if statement because those
* also have () and {
********************************************************************/
std::vector<int> functionChecker(std::vector<std::string> input) {
	// Check if the first word is 'for' or 'while'
	std::vector<int> functionPos;

	bool forWhileIf = false;
	for (int i = 0; i < input.size(); i++) {
		if ((input[i].substr(0, 3) == "for" || input[i].substr(0, 5) == "while")||(input[i].substr(0, 2) == "if" || input[i].substr(0, 7) == "else if")) {
			forWhileIf = true;
		}
		else {
			forWhileIf = false;
		}

		bool openPar = false;
		bool closePar = false;
		bool openBrac = false;
		if (!forWhileIf) {
			for (int j = 0; j < input[i].length(); j++) {
				if (input[i].at(j) == '{') {
					openBrac = true;
				}
				if (input[i].at(j) == '(') {
					openPar = true;
				}
				if (input[i].at(j) == ')') {
					closePar = true;
				}
			}
		}
		if ((openPar && closePar) && openBrac) {
			functionPos.push_back(i);
		}
	}
	return functionPos;	
}

/*******************************************************************
*	commentChecker(vector<string> input)
*	This function will checck for psuedocode and comments on their
* own line, as well as comments that occur after code
********************************************************************/
std::vector<int> commentCheckerSingle(std::vector<std::string> input) {
	// make a variable to store in line comment positions
	std::vector<int> commentPos;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].length() > 1) {
			for (int j = 0; j < input[i].length() - 1; j++) {
				if (input[i].substr(j, 2) == "//") {
					commentPos.push_back(i);
					j = input[i].length();
				}
			}
		}
	}
	return commentPos;
}

/*******************************************************************
*	commentBlockChecker(vector<string input)
*	Checks the file for where comment blocks are located, where they
* start and where they end
********************************************************************/
std::vector<std::string> commentBlockChecker(std::vector<std::string> input) {
	// make a variable to store comment block pos
	std::vector<std::string> commentBlockPos;


	for (int i = 0; i < input.size(); i++) {
		bool comment = false;
		if (input[i].length() > 0) {
			for (int j = 0; j < input[i].length() - 1; j++) {
				if (input[i].substr(j, 2) == "/*") {
					comment = true;
					commentBlockPos.push_back("01 " + std::to_string(i));
					j = input[i].length();
				}
				else if (input[i].substr(j, 2) == "*/") {
					comment = false;
					commentBlockPos.push_back("02 " + std::to_string(i));
					j = input[i].length();
				}
			}
		}
	}
	return commentBlockPos;
}

/*******************************************************************
*	parseCommentBlock(vector<string>
********************************************************************/
std::vector<int> parseCommentBlock(std::vector<std::string> commentBlockVector, std::string checker) {
	std::vector<int> commentBlock;
	for (int i = 0; i < commentBlockVector.size(); i++) {
		if (commentBlockVector[i].substr(0, 2) == "01") {
			if (checker == "01") {
				commentBlock.push_back(std::stoi(commentBlockVector[i].substr(3, commentBlockVector[i].length())));
			}
		}
		else if (commentBlockVector[i].substr(0, 2) == "02") {
			if (checker == "02") {
				commentBlock.push_back(std::stoi(commentBlockVector[i].substr(3, commentBlockVector[i].length())));
			}
		}
	}
	return commentBlock;
}


/******************************************************************************
*	displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out any file passed into it
******************************************************************************/
void displayFile(std::vector<std::string> fileToPrint) {
	for (const auto& str : fileToPrint) {
		std::cout << str << std::endl; // Outputs cleaned strings
	}
}

void displayFile(std::vector<int> fileToPrint) {
	for (const auto& str : fileToPrint) {
		std::cout << str << std::endl; // Outputs cleaned strings
	}
}

/******************************************************************************
*	compileDescription(vector<string> oldDescription, vector<int> input, string description)
*	this will take a vector of numbers and add the 'description' to a new vector
* and then return the new vector with added description elements
******************************************************************************/
std::vector<std::string> compileDescription(std::vector<std::string> oldDescription, std::vector<int> input, std::string description) {
	// stub function
	return oldDescription;
}

int main() {
	// description, make sure to put files in this directory, etc
	color("yellow");
	std::cout << "Welcome, this program pulls from files in the compiled code's directory; namely, the files ";
	std::cout << "you have in this project's folder.\n";
	std::cout << "Make sure to move/copy the source/header files of the project you are grading into this project's folder.\n";
	color("reset");

	// ask them to input a file name
	std::vector<std::string> file = copyFile();

	// Description of each line <<<NEED TO DO>>>
	std::vector<std::string> fileLineDesc;

	// Loop through each element of 'file' and add the string of i + 1 to 'fileLineDesc'
	for (size_t i = 0; i < file.size(); ++i) {
		fileLineDesc.push_back(std::to_string(i + 1));  // Convert i + 1 to string  
	}

	color("white");
	std::cout << "Every line in the function" << std::endl;
	color("red");
	displayFile(fileLineDesc);
	color("reset");

	// unnested file
	std::vector<std::string> unnestedFile = removeNesting(file);

	// Lines where functions are located
	std::vector<int> functionLines = functionChecker(unnestedFile);

	// Lines where single Line comments are located
	std::vector<int> commentLinesSingle = commentCheckerSingle(unnestedFile);
	
	std::vector<std::string> commentLinesBlock = commentBlockChecker(unnestedFile);

	// Prints out Function Position
	color("white");
	std::cout << "Functions on lines: " << std::endl;
	color("cyan");
	displayFile(functionLines);

	// Prints out Single Line Comment Positions
	color("white");
	std::cout << "Comments on lines: " << std::endl;
	color("green");
	displayFile(commentLinesSingle);

	std::vector<int> commentBlockStart = parseCommentBlock(commentLinesBlock, "01");
	std::vector<int> commentBlockEnd = parseCommentBlock(commentLinesBlock, "02");

	color("white");
	std::cout << "Comment block starts: " << std::endl;
	color("green");
	displayFile(commentBlockStart);
	color("white");
	std::cout << "Comment block ends: " << std::endl;
	color("green");
	displayFile(commentBlockEnd);
	color("reset");
}

// STYLE GUIDE CHECK
// check must have comment block above every function
// warning if function doesn't contain comments
// proper nesting and indents

// FUNCTIONALITY TEST