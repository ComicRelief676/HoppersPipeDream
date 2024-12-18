#include <iostream>
#include <fstream> // allows us to pull from files
#include <string>
#include <vector>
#include "Color.h"
#include "Print.h"
#include "Comments.h"

/********************************************************************
* getFileName()
* 	This function will ask the user to input a file name from
* 	the current directory, then returns the file name
********************************************************************/
std::string getFileName() {

	std::string fileName;
	color("magenta");
	std::cout << "Input the name of the file you want to auto-grade (example: Item.txt):" << std::endl;
	color("reset");
	std::cin >> fileName;
	return fileName;
}

/********************************************************************
* copyFile()
*	This function takes the name of a file from the current
* 	directory, copies every line of that file to a vector, then
* 	returns the vector
********************************************************************/
std::vector<std::string> copyFile() {
	bool success = true;
	std::ifstream inputFile;
	do {
		// asks user for the file path 
		std::string fileName = getFileName();
		inputFile.open(fileName);
		if (!inputFile) { // Check if the file opened successfully
			std::cerr << "Error opening file: " << fileName << std::endl;
			success = false;
		}
		// If there are no issues
		else {
			success = true;
		}
	} while (!success);

	// Vector to store all the lines from the opened File
	std::vector<std::string> lines;
	// variable that is used to pass line values through
	std::string line;

	// Read each line from the file and store it in the vector
	while (std::getline(inputFile, line)) {
		lines.push_back(line);
	}

	inputFile.close(); // Closes the file
	return lines;
}

/******************************************************************************
* removeNesting(std::vector<std::string> input)
*	Removes all nesting from the file and returns the file unnested
******************************************************************************/
std::vector<std::string> removeNesting(std::vector<std::string> input) {
	// Loops through each line
	for (int i = 0; i < input.size(); i++) {
		if (input[i].length() > 1) {
			//Loops through removing each space
			while (input[i].at(0) == 32 || input[i].at(0) == 9) {
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
std::vector<int> functionChecker(std::vector<std::string> input, std::vector<std::string> commentVec) {
	// Check if the first word is 'for' or 'while'
	std::vector<int> functionPos;

	// if the line is actually a for, while, or if condition, skip this line becuase those have () and { but aren't function declarations
	bool forWhileIf = false;
	for (int i = 0; i < input.size(); i++) {
		if ((input[i].substr(0, 3) == "for" || input[i].substr(0, 5) == "while") || (input[i].substr(0, 2) == "if" || input[i].substr(0, 7) == "else if")) {
			forWhileIf = true;
		}
		else {
			forWhileIf = false;
		}

		// now check to see if there is an open parenthesis, close par, and open bracket
		bool openPar = false;
		bool closePar = false;
		bool openBrac = false;

		// if the line doesn't start with for, while, or if, it will do this thing
		if (!forWhileIf) {
			// It will loop through each position in the line
			for (int j = 0; j < input[i].length(); j++) {
				// checks to see if this position is commented
				if (commentVec[i][j] == 48) {
					if (input[i][j] == 123) {
						openBrac = true;
					}
					if (input[i][j] == 40) {
						openPar = true;
					}
					if (input[i][j] == 41) {
						closePar = true;
					}	
				}
			}
		}
		// when we have determined that this line is a function declaration, return this line
		if ((openPar && closePar) && openBrac) {
			functionPos.push_back(i);
		}
	}
	return functionPos;
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

/******************************************************************************
* std::vector<int> emptyLnChecker(std::vector<std::string> input)
*	Checks for and returns empty line locations
******************************************************************************/
std::vector<int> emptyLnChecker(std::vector<std::string> input) {
	// vector for storing empty line locations
	std::vector<int> emptyLns;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == "") {
			emptyLns.push_back(i);
		}
	}
	return emptyLns;
}

/******************************************************************************
* functionCommentBlocks(vector<int> functionLns, vector<int> commentBlkEnd)
*	This function will check to see if there is a comment block directly above
*	a function
******************************************************************************/
std::vector<bool> functionCommentBlocks(std::vector<int> functionLns, std::vector<CommentBlock> commentBlocks) {
	std::vector<bool> isCommentBlocked;
	for (int i = 0; i < functionLns.size(); i++) { // this will loop through each line that has a function on it

		for (int j = 0, size = commentBlocks.size(); j < size; j++) { // this will loop through all of the comment block ends to see if there is a comment block above the function
			if (functionLns[i] == (commentBlocks[j].endLine + 1)) {
				isCommentBlocked.push_back(true);
				break;
			}
			if (j == size - 1) {
				isCommentBlocked.push_back(false);
			}
		}
	}
	return isCommentBlocked;
}

/******************************************************************************
* std::vector<int> bracketFinder(std::vector<std::string> input
*	This function will return a vector that says what the indentation should
* be for each line
******************************************************************************/
std::vector<int> bracketFinder(std::vector<std::string> input, std::vector<std::string> commentVec) {
	std::vector<int> indentation;
	int num = 0;
	for (int i = 0, size = input.size(); i < size; i++) {
		for (int j = 0, length = input[i].length(); j < length; j++) {
			if (commentVec[i][j] == 48) {
				if (input[i][j] == 123) {
					num++;
				}
				if (input[i][j] == 125) {
					num--;
				}
			}
		}
		indentation.push_back(num);
	}
	return indentation;
}




int main() {
	// description, make sure to put files in this directory, etc
	color("yellow");
	std::cout << "Welcome, this program pulls from files in the compiled code's directory; namely, the files ";
	std::cout << "you have in this project's folder.\n";
	std::cout << "Make sure to move/copy the source/header files of the project you are grading into this project's folder.\n";
	color("reset");



	// SETS UP FILE

	// ask them to input a file name
	std::vector<std::string> file = copyFile();
	// unnested file
	std::vector<std::string> unnestedFile = removeNesting(file);
	// lines that are empty ""
	std::vector<int> emptyLines = emptyLnChecker(unnestedFile);



	// BUILDS COMMENT VECTOR
	
	// Lines where single Line comments are located
	std::vector<SingleLine> commentLinesSingle = commentCheckerSingle(unnestedFile);
	// Finds all starts and ends of Comment Blocks
	std::vector<CommentBlock> commentBlocks = commentBlockChecker(unnestedFile, commentLinesSingle);
	// This vector has the comment status of each line and position in the file stored [line][pos]
	std::vector<std::string> commentVec = commentTotal(commentLinesSingle, commentBlocks, file);
	


	// STUFF WITH FUNCTIONS

	// Lines where functions are located
	std::vector<int> functionLines = functionChecker(unnestedFile, commentVec);
	// Sees which functions are properly comment blocked
	std::vector<bool> functionsCommentBlocked = functionCommentBlocks(functionLines, commentBlocks);


	std::vector<int> indentation = bracketFinder(unnestedFile, commentVec);
	std::vector<commentBlkSpecs> blockSpecs = commentBlockSpecifications(unnestedFile, commentBlocks);
	debugPrint(blockSpecs);

	// IDK STUFF
	
	// Description of each line <<<NEED TO DO>>>
	std::vector<std::string> fileLineDesc;

	// Loop through each element of 'file' and add the string of i + 1 to 'fileLineDesc'
	for (size_t i = 0; i < file.size(); ++i) {
		fileLineDesc.push_back(std::to_string(i + 1));  // Convert i + 1 to string  
	}
	return 0;
}

// STYLE GUIDE CHECK
// check must have comment block above every function
// warning if function doesn't contain comments -- how many comments lines in entire program comments/total lines ratio ???
// proper nesting and indents

// FUNCTIONALITY TEST

/*
int improperCommentBlock = 0;
We should check to see if the number of '*'s in the comment block openings/closings are greater than 150 or less than 50
if so we should increment improperCommentBlock
*/

/*
create function that checks for variables on lines, and variable names
*/

/*
We need to create a function that finds a functions bounds
*/

/*
DO TO FOR THE DESCRIPTION
We will need to put combine all vectors
sort this combined vector list, so that it has an ordered description
*/


/*
have an integer value assigned to each bracket to say how many \t's it should have
function that finds all opening and closing brackets
add if open, subtract if close
check all lines in between
*/
