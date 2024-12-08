#include "Print.h"

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
void displayFile(std::vector<std::string> fileToPrint) {
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
* displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out a std::vector<int> that is passed into it
******************************************************************************/
void displayFile(std::vector<CommentBlock> fileToPrint) {
	int i = 0;
	for (const auto& str : fileToPrint) {
		std::cout << "Start line: " << fileToPrint[i].startLine << std::endl;
		std::cout << "Start line position: " << fileToPrint[i].startPos << std::endl;
		std::cout << "End line: " << fileToPrint[i].endLine << std::endl;
		std::cout << "End line position: " << fileToPrint[i].endPos << std::endl;
		i++;
	}
}


/******************************************************************************
* displayFile(std::vector<std::string> fileToPrint)
*	This will fully print out a std::vector<int> that is passed into it
******************************************************************************/
void displayFile(std::vector<commentBlkSpecs> fileToPrint) {
	int i = 0;
	for (const auto& str : fileToPrint) {
		std::cout << "Similar Lengths: " << fileToPrint[i].similarLengths << std::endl;
		std::cout << "Acceptable Top Length: " << fileToPrint[i].acceptableTopLength << std::endl;
		std::cout << "Acceptable Bottom Length: " << fileToPrint[i].acceptableBottomLength << std::endl;
		std::cout << "Top Length: " << fileToPrint[i].topLnLen << std::endl;
		std::cout << "Bottom Length: " << fileToPrint[i].bottomLnLen << std::endl;
		std::cout << "Acceptable Spacing: " << fileToPrint[i].acceptableSpacing << std::endl;
		std::cout << "mid lines have astricks: " << fileToPrint[i].midLnsHaveAstricks << std::endl;
		std::cout << "mid lines are in bounds: " << fileToPrint[i].midLnsInBounds << std::endl;
		std::cout << "" << std::endl;
		i++;
	}
}

/******************************************************************************
* void debugPrint(desc, descColor, item, itemColor)
*	This function is for debugging, it will take a description and print it out
* in white as default or as descColor, then it will display a vector in a
* designated color
******************************************************************************/
void debugPrint(std::vector<std::string> item, std::string desc, std::string itemColor, std::string descColor) {
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
void debugPrint(std::vector<int> item, std::string desc, std::string itemColor, std::string descColor) {
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
void debugPrint(std::vector<bool> item, std::string desc, std::string itemColor, std::string descColor) {
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
void debugPrint(std::vector<CommentBlock> item, std::string desc, std::string itemColor, std::string descColor) {
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
void debugPrint(std::vector<commentBlkSpecs> item, std::string desc, std::string itemColor, std::string descColor) {
	color(descColor);
	std::cout << desc << std::endl;
	color(itemColor);
	displayFile(item);
	color("reset");
}