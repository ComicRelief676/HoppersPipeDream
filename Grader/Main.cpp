#include <iostream>
#include <fstream> // allows us to pull from files
#include <string>
#include <vector>
#include "Color.h"

// function prototyping / declaration
std::string getFileName();
std::vector<std::string> copyFile();
std::vector<std::string> removeNesting(std::vector<std::string> input);
std::vector<int> functionChecker(std::vector<std::string> input);
std::vector<int> commentCheckerSingle(std::vector<std::string> input);
std::vector<std::string> commentBlockChecker(std::vector<std::string> input);
std::vector<int> parseCommentBlock(std::vector<std::string> commentBlockVector, std::string checker);
void displayFile(std::vector<std::string> fileToPrint);
void displayFile(std::vector<int> fileToPrint);
std::vector<std::string> compileDescription(std::vector<std::string> oldDescription, std::vector<int> input, std::string description);

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
std::vector<int> functionChecker(std::vector<std::string> input, std::vector<int> commentBlockLn) {
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
		bool isCommented = false; // we don't want to include functions that are commented out
		bool openPar = false;
		bool closePar = false;
		bool openBrac = false;
		if (!forWhileIf) {
			for (int j = 0; j < input[i].length(); j++) {
				if (input[i].substr(j, 2) == "//") {
					isCommented = true;
				}
				if (!isCommented) {
					for (int j = 0; j < commentBlockLn.size(); j++) {
						if (i == commentBlockLn[j]) {
							isCommented = true;
						}
					}
					if (!isCommented) {
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
			}
		}
		// when we have determined that this line is a function declaration, return this line
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
				// check to see if this line is a comment anywhere on the line
				if (input[i].substr(j, 2) == "//") {
					// if this line is a comment, save this line to vector
					commentPos.push_back(i);
					// we only want to save a line once if it has a comment, so
					// move to the next line after we determine this one has a comment
					j = input[i].length();
				}
			}
		}
	}
	// return vector with all the lines that have comments
	return commentPos;
}

/***************************************************************************************************
*	commentPosition(vector<string> input, vector<int> commentBlock)
*	This function will return a new vector that cotains the commented status of each character
* in the file, 0 will represent uncommented character, while 1 will represnt a commented charcter
****************************************************************************************************/
std::vector<std::string> baconator(std::vector<std::string> input, std::vector<int> commentBlock) {
	std::vector<std::string> bacon;
	for (int i = 0; i < input.size(); i++) {
		// This is the point where the comment starts on the line
		int commentPos = input[i].length();
		std::string commentLns = "";

		// says if there's comment block there
		for (int j = 0; j < commentBlock.size(); j++) {
			if (commentBlock[j] == i) {
				commentPos = 0;
			}
		}


		// this should check for inline comments and see if stuff is commented out or not
		if (input[i].length() > 1) {
			// this for loop finds the start location of "//"
			for (int j = 0; j < input[i].length() - 1; j++) {
				// check to see if this line is a comment anywhere on the line
				if (input[i].substr(j, 2) == "//") {
					commentPos = j;
					j = input[i].length();
				}
			}
		}
		// this will take the commentPos - the position of the start of a comment and add them to commentLns to return to the vector
		// print 0's for uncommented, 1's for commented
		for (int j = 0; j < input[i].length(); j++) {
			if (j < commentPos) {
				commentLns += "0";
			}
			else {
				commentLns += "1";
			}
		}
		bacon.push_back(commentLns);
	}
	return bacon;
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
		bool isAlreadyCommented = false; // this is for if there is a // before the opening of a comment block, so it doesn't count as a cmtBlock, but just a comment
		// have a variable to see if we are already in a comment block
		// We dont want two comment block from one line if for example:
		// is one comment block but might be saved as two starts to one
		bool comment = false;
		if (input[i].length() > 0) {
			for (int j = 0; j < input[i].length() - 1; j++) {
				if (isAlreadyCommented || input[i].substr(j, 2) == "//") {
					isAlreadyCommented = true;
				}
				else {
					if (input[i].substr(j, 2) == "/*" && !comment) {
						comment = true;
						// if the value starts with 01, it is the start of a comment block
						commentBlockPos.push_back("01 " + std::to_string(i));
						j = input[i].length();
					}
					else if (input[i].substr(j, 2) == "*/") {
						comment = false;
						// if it starts with 02, it will be the end
						commentBlockPos.push_back("02 " + std::to_string(i));
						j = input[i].length();
					}
				}
			}
		}
	}
	// return the lines with comment block starts and ends
	return commentBlockPos;
}

/*******************************************************************
* parseCommentBlock(vector<string>
*	This function will parse the returned statements from
*	commentBlockChecker() and check if they are either opening
*	or closing based on the std::string checker passed
*	It will then return the respective lines
********************************************************************/
std::vector<int> parseCommentBlock(std::vector<std::string> commentBlockVector, std::string checker) {
	// we will be given a string in the form xx xxx, where the first two xx's are if starting/ending cmb (01/02)
	// and the everything after that is the line it can be found on(line:139)
	std::vector<int> commentBlockLn;
	for (int i = 0; i < commentBlockVector.size(); i++) {
		if (commentBlockVector[i].substr(0, 2) == checker) {
			commentBlockLn.push_back(std::stoi(commentBlockVector[i].substr(3, commentBlockVector[i].length())));
		}
	}
	return commentBlockLn;
}


/******************************************************************************
* displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out a std::vector<std::string> that is passed into it
******************************************************************************/
void displayFile(std::vector<std::string> fileToPrint) {
	for (const auto& str : fileToPrint) {
		std::cout << str << std::endl; // Outputs cleaned strings
	}
}

/******************************************************************************
* displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out a std::vector<int> that is passed into it
******************************************************************************/
void displayFile(std::vector<int> fileToPrint) {
	for (const auto& str : fileToPrint) {
		std::cout << str << std::endl; // Outputs cleaned strings
	}
}

/******************************************************************************
* displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out a std::vector<bool> that is passed into it
******************************************************************************/
void displayFile(std::vector<bool> fileToPrint) {
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

/******************************************************************************
* std::vector<int> commentBlockConcatenation(std::vector<int> Start, std::vector<int> End)
*	This function will find every line that is a comment block, and return that vector
******************************************************************************/
std::vector<int> commentBlockConcatenation(std::vector<int> start, std::vector<int> end) {
	std::vector<int> commentBlockLines;
	// loops through lines before the last value in End
	for (int i = 0; i < start.size() && i < end.size(); i++) {

		int j = start[i];
		while (j <= end[i]) {

			commentBlockLines.push_back(j);
			j++;
		}
	}

	return commentBlockLines;
}

/******************************************************************************
* void debugPrint(desc, descColor, item, itemColor)
*	This function is for debugging, it will take a description and print it out
* in white as default or as descColor, then it will display a vector in a
* designated color
******************************************************************************/
void debugPrint(std::vector<std::string> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white") {
	color(descColor);
	std::cout << desc << std::endl;
	color(itemColor);
	displayFile(item);
	color("reset");
}

/******************************************************************************
* void debugPrint(desc, descColor, item, itemColor)
*	Overloaded version for int vectors
******************************************************************************/
void debugPrint(std::vector<int> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white") {
	color(descColor);
	std::cout << desc << std::endl;
	color(itemColor);
	displayFile(item);
	color("reset");
}

/******************************************************************************
* void debugPrint(desc, descColor, item, itemColor)
*	Overloaded version for int vectors
******************************************************************************/
void debugPrint(std::vector<bool> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white") {
	color(descColor);
	std::cout << desc << std::endl;
	color(itemColor);
	displayFile(item);
	color("reset");
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

// our program freaks the heck out with this function so something is clearly messed the heck up over here -- up to you two guys in the future.

// this function will check to see if there is a comment block above the function,
// it will also make sure the top and bottom have the same # of *'s, and 50<*<150
//std::vector<std::string> functionCommentBlocks(std::vector<int> functionLns, std::vector<int> commentBlkStart, std::vector<int> commentBlkEnd, std::vector<std::string> file) {
//		// (is there a comment block) (are they the same length) (is opening too short) (is closing too short) (is opening too long) (is closing too long)
//		// ex: "1 0 1 0 1 0 1 ";
//		std::vector<std::string> functionAssessment;
//
//
//	for (int i = 0; i < functionLns.size(); i++) {
//		int commentBlockPos = 0;
//		bool isCommentBlock = false;
//		std::string assessment;
//		
//		for (int j = 0; j < commentBlkEnd.size(); j++) {
//			// checks if the line above a function has a comment block end above it
//			if (functionLns[i] == (commentBlkEnd[j] + 1)) {
//				commentBlockPos = j;
//				j = commentBlkEnd.size();
//				isCommentBlock = true;
//			}
//		}
//		// Returns '0' if there is no comment block, '1' if there is one
//		if (!isCommentBlock) {
//			assessment = "0";
//		} else {
//			assessment = "1";
//			
//			// checks if the start and end are the same length
//			if (file[commentBlkEnd[commentBlockPos]] != file[commentBlkStart[commentBlockPos]]) {
//				assessment += " 0";
//			} else {
//				assessment += " 1";
//			}
//
//			// checks if the start is smaller than 50
//			if (file[commentBlkStart[commentBlockPos]].length() < 50) {
//				assessment += " 0";
//			} else {
//				assessment += " 1";
//			}
//
//			// checks of the end is smaller than 50
//			if (file[commentBlkEnd[commentBlockPos]].length() < 50) {
//				assessment += " 0";
//			} else {
//				assessment += " 1";
//			}
//
//			// checks if the start is greater than 150
//			if (file[commentBlkStart[commentBlockPos]].length() > 150) {
//				assessment += " 0";
//			} else {
//				assessment += " 1";
//			}
//
//			// checks if the end is greater than 150
//			if (file[commentBlkEnd[commentBlockPos]].length() > 150) {
//				assessment += " 0";
//			} else {
//				assessment += " 1";
//			}
//		}
//		functionAssessment.push_back(assessment);
//	}
//	return functionAssessment;
//}

/******************************************************************************
* functionCommentBlocks(vector<int> functionLns, vector<int> commentBlkEnd)
*	This function will check to see if there is a comment block directly above
*	a function
******************************************************************************/
std::vector<bool> functionCommentBlocks(std::vector<int> functionLns, std::vector<int> commentBlkEnd) {
	std::vector<bool> isCommentBlocked;
	for (int i = 0; i < functionLns.size(); i++) { // this will loop through each line that has a function on it
		bool isCommented = false;
		for (int j = 0; j < commentBlkEnd.size(); j++) { // this will loop through all of the comment block ends to see if there is a comment block above the function
			if (functionLns[i] == (commentBlkEnd[j] + 1)) {
				isCommented = true;
			}
		}
		isCommentBlocked.push_back(isCommented);
	}
	return isCommentBlocked;
}

/******************************************************************************
* std::vector<int> bracketFinder(std::vector<std::string> input
*	This function will return a vector that says what the indentation should
* be for each line
******************************************************************************/
std::vector<int> bracketFinder(std::vector<std::string> input, std::vector<int> commentBlockLines) {
	int num = 0;
	std::vector<int> indents;
	bool commentBlock = false;
	std::cout << "here" << std::endl;

	for (int i = 0; i < input.size(); i++) {
		std::cout << i << std::endl;
		// check to see if line 'i' is in commentblock b/c that means its commentd
		for (int j = 0; j < commentBlockLines.size(); j++) {
			std::cout << "Is a comment block line: " << (j < commentBlockLines.size()) << std::endl;
			if (i == commentBlockLines[j]) {
				commentBlock = true;
			}
		}
		if (!commentBlock) {
			std::cout << "Is not a comment block line " << std::endl;
			// have a checker in the j for loop to see if // appears before it

			for (int j = 0; j < input[i].length(); j++) {
				if (input[i][j] == '{') {
					num++;
				}
				if (input[i][j] == '}') {
					num--;
				}
			}
		}
		indents.push_back(num);
		commentBlock = false;
	}
	return indents;
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

	// unnested file
	std::vector<std::string> unnestedFile = removeNesting(file);

	// Lines where single Line comments are located
	std::vector<int> commentLinesSingle = commentCheckerSingle(unnestedFile);
	// lines that are empty ""
	std::vector<int> emptyLines = emptyLnChecker(unnestedFile);

	// Finds all starts and ends of Comment Blocks
	std::vector<std::string> commentBlocksStartEnd = commentBlockChecker(unnestedFile);
	std::vector<int> commentBlockStart = parseCommentBlock(commentBlocksStartEnd, "01");
	std::vector<int> commentBlockEnd = parseCommentBlock(commentBlocksStartEnd, "02");
	// This variable has all lines that are parts of Comment Blocks
	std::vector<int> commentBlockLines = commentBlockConcatenation(parseCommentBlock(commentBlocksStartEnd, "01"), parseCommentBlock(commentBlocksStartEnd, "02"));

	// Lines where functions are located
	std::vector<int> functionLines = functionChecker(unnestedFile, commentBlockLines);

	std::vector<bool> areFunctionsCommentBlocked = functionCommentBlocks(functionLines, commentBlockEnd);


	/*std::vector<std::string> isPositionCommented = baconator(unnestedFile, commentBlockLines);
	debugPrint(isPositionCommented);*/

	debugPrint(baconator(unnestedFile, commentBlockLines));

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

// TO DO figure out multi-line single line comments /*like this for example*/