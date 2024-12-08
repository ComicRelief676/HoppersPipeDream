#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

struct CommentBlock {
	int startLine;
	int startPos;
	int endLine;
	int endPos;
};

struct SingleLine {
	int lineNum;
	int linePos;
};

struct commentBlkSpecs {
	bool similarLengths;
	bool acceptableTopLength;
	bool acceptableBottomLength;
	int topLnLen;
	int bottomLnLen;
	bool acceptableSpacing;
	bool midLnsHaveAstricks;
	bool midLnsInBounds;
};

std::vector<SingleLine> commentCheckerSingle(std::vector<std::string> input);

std::vector<CommentBlock> commentBlockChecker(const std::vector<std::string>& input, std::vector<SingleLine> singleLns);

std::vector<std::string> commentTotal(std::vector<SingleLine> singleLns, std::vector<CommentBlock> blockLns, std::vector<std::string> file);
std::vector<commentBlkSpecs> commentBlockSpecifications(std::vector<std::string> file, std::vector<CommentBlock> commentBlk);
