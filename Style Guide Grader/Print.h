#pragma once
#include <iostream>
#include <vector>
#include "Color.h"
#include <string>
#include "Comments.h"

void displayFile(std::vector<int> fileToPrint);

void displayFile(std::vector<std::string> fileToPrint);

void displayFile(std::vector<bool> fileToPrint);

void displayFile(std::vector<CommentBlock> fileToPrint);
void displayFile(std::vector<commentBlkSpecs> fileToPrint);

// functions below for debug use only, not intended for finished project

void debugPrint(std::vector<std::string> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white");

void debugPrint(std::vector<int> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white");

void debugPrint(std::vector<bool> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white");

void debugPrint(std::vector<CommentBlock> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white");
void debugPrint(std::vector<commentBlkSpecs> item, std::string desc = "debugPrint:", std::string itemColor = "red", std::string descColor = "white");
