#include "Comments.h"

/*******************************************************************
*	commentChecker(vector<string> input)
*	This function will checck for psuedocode and comments on their
* own line, as well as comments that occur after code
********************************************************************/
std::vector<SingleLine> commentCheckerSingle(std::vector<std::string> input) {
	// make a variable to store in line comment positions
	std::vector<SingleLine> commentPos;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].length() > 1) {
			for (int j = 0; j < input[i].length() - 1; j++) {
				// check to see if this line is a comment anywhere on the line
				if (input[i].substr(j, 2) == "//") {
					SingleLine var = { i, j };
					// if this line is a comment, save this line to vector
					commentPos.push_back(var);
					// we only want to save a line once if it has a comment, so
					// move to the next line after we determine this one has a comment
					break;
				}
			}
		}
	}
	// return vector with all the lines that have comments
	return commentPos;
}

/***********************************************************************************************
*	commentBlockChecker(vector<string> input)
*	Finds comment blocks, each comment block has 4 atritubtes including start line, start pos,
* end line, and end position. Returns a vector that has each of these 4 attritubes in each
* item of the vector
************************************************************************************************/
std::vector<CommentBlock> commentBlockChecker(const std::vector<std::string>& input, std::vector<SingleLine> singleLns) {
	std::vector<CommentBlock> commentBlocks;
	bool commented = false;
	int startLine = 0, startCol = 0;

	for (int i = 0; i < input.size(); ++i) {
		const std::string& line = input[i];
		for (int j = 0; j < line.size(); ++j) {
			commented = false;

			// This will check to see if the current position [i][j] is commented under a single line comment
			for (int k = 0; k < singleLns.size(); k++) {
				if (i == singleLns[k].lineNum) {
					if (j >= singleLns[k].linePos) {
						commented = true;
					}
				}
			}

			// if it's not commented it will add a start position
			if (!commented) {
				if (j + 1 < line.size() && line.substr(j, 2) == "/*") {
					startLine = i;
					startCol = j;
				}
				if (j + 1 < line.size() && line.substr(j, 2) == "*/") {
					CommentBlock block = { startLine, startCol, i, j + 2 };
					commentBlocks.push_back(block);
				}
			}
		}
	}

	return commentBlocks;
}

/***************************************************************************************************
*	commentTotal()
*	Takes the lines and positions of the inline comments on top of the start and endlines and
* start and end positions of the commentBlocks
****************************************************************************************************/
std::vector<std::string> commentTotal(std::vector<SingleLine> singleLns, std::vector<CommentBlock> blockLns, std::vector<std::string> file) {
	// THIS FUNCTION IS THE FUNCTION THAT WE DID NOT DO BUT WE NEED TO DO IT BUT WE HAVENT YET SO WE SHOULD PROBABLY DO IT EVEN THOUGH WE HAVENT DONE IT YET SO LETS DO IT 
	std::vector<std::string> bigMac;
	std::string line;
	// for loop that will loop through each line in the file

			// this will tell us if there's a multiLn comment
	bool isMultLn = false;
	// this is that position in the struct where the comment info is helds
	int multLn = 0;

	for (int i = 0; i < file.size(); i++) {
		line = "";
		// if we are in a multiLine comment and we move past it, isMultLn becomes false again
		if (isMultLn && i > blockLns[multLn].endLine) {
			isMultLn = false;
		}
		// if this line has a single comment this will be true
		bool isSingleLn = false;
		// if isSingleLn is true, this will be the position in singleLns that has the comment's data
		int singleLn = 0;


		if (!isMultLn) {
			// This will check to see if there is a single line comment on line 'i'
			for (int j = 0; j < singleLns.size(); j++) {
				if (i == singleLns[j].lineNum) {
					isSingleLn = true;
					singleLn = j;
					break;
				}
			}

			// This will check to see if there's a multi line comment starting on 'i'
			for (int j = 0; j < blockLns.size(); j++) {
				if (i == blockLns[j].startLine) {
					isMultLn = true;
					multLn = j;
					break;
				}
			}
		}

		// if line 'i' has a single line comment it will do this thing
		if (isSingleLn) {
			// loops through each position in the line
			for (int j = 0; j < file[i].length(); j++) {
				// if the area is uncommented
				if (j < singleLns[singleLn].linePos) {
					line += "0";
				}
				// if it is commented
				else {
					line += "1";
				}
			}
		}


		// if line 'i' has a multi line comment it will do that thing
		if (isMultLn) {
			// loops through each position in the line
			for (int j = 0; j < file[i].length(); j++) {
				if (blockLns[multLn].startLine == blockLns[multLn].endLine) {
					if (j >= blockLns[multLn].startPos && j <= blockLns[multLn].endPos) {
						line += "1";
					}
					else {
						line += "0";
					}
					continue;
				}
				if (blockLns[multLn].startLine == i) {
					if (j >= blockLns[multLn].startPos) {
						line += "1";
					}
					else {
						line += "0";
					}
					continue;
				}
				// if i is the last line of the comment block
				if (i == blockLns[multLn].endLine) {

					// if we havent hit the end of the comment
					if (j < blockLns[multLn].endPos) {

						line += "1";
					}
					// if we reach or pass the end of the comment
					else {
						std::cout << "We reach the last line of the comment but have reached the end of the comment" << std::endl;

						line += "0";
					}
				}
				// if I is not the the last line of the comment
				else {
					line += "1";
				}
			}
		}
		if (!isMultLn && !isSingleLn) {
			for (int j = 0; j < file[i].length(); j++) {
				line += "0";
			}
		}

		bigMac.push_back(line);
	}
	return bigMac;
}



/************************************************************************************************************
* 70-110 chars long
* start with asterick
* start and end same length or 1 characters off aksd
* middle no more than 4 of top/bottom
************************************************************************************************************/
std::vector<commentBlkSpecs> commentBlockSpecifications(std::vector<std::string> file, std::vector<CommentBlock> commentBlk) {
	std::vector<commentBlkSpecs> specs;
	commentBlkSpecs block;

	// This loops through each comment block
	for (int i = 0, size = commentBlk.size(); i < size; i++) {
		block.topLnLen = file[commentBlk[i].startLine].length();
		block.bottomLnLen = file[commentBlk[i].endLine].length();

		if (block.topLnLen > 110) {
			//std::cout << file[commentBlk[i].startLine].length() <<  "This is long" << std::endl;
			block.acceptableTopLength = false;
		}
		else if (block.topLnLen < 70) {
			//std::cout << file[commentBlk[i].startLine].length() << "This is short" << std::endl;
			block.acceptableTopLength = false;

		}
		else {
			//std::cout << file[commentBlk[i].startLine].length() << "This is just right" << std::endl;
			block.acceptableTopLength = true;

		}
		if (block.bottomLnLen > 110) {
			//std::cout << file[commentBlk[i].endLine].length() <<  "This is long" << std::endl;
			block.acceptableBottomLength = false;
		}
		else if (block.bottomLnLen < 70) {
			//std::cout << file[commentBlk[i].endLine].length() << "This is short" << std::endl;
			block.acceptableBottomLength = false;

		}
		else {
			//std::cout << file[commentBlk[i].endLine].length() << "This is just right" << std::endl;
			block.acceptableBottomLength = true;

		}
		int lengthDifference = block.topLnLen - block.bottomLnLen;
		if (abs(lengthDifference) <= 1) {
			block.similarLengths = true;
		}
		else {
			block.similarLengths = false;
		}

		block.midLnsHaveAstricks = true;
		block.acceptableBottomLength = true;
		block.midLnsInBounds = true;

		for (int j = block.topLnLen + 1, k = block.bottomLnLen; j < k; j++) {
			if (file[j][0] != '*') {
				block.midLnsHaveAstricks = false;
			}
			if (file[j].length() <= 5) {
				block.acceptableBottomLength = false;
			}
			if (file[j].length() > block.topLnLen + 5) {
				block.midLnsInBounds = false;
			}
		}
		specs.push_back(block);
	}
	return specs;
}