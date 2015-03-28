#pragma once

#include <iostream>
#include <fstream>
#include "ChaseTest.h"
#include "ThirdNF.h"
#include "Relation.h"
#include "FD.h"
#include "Utils.h"

// 3NF
void perform3NF();
void getRelation(Relation& out);
void getFDs(std::vector<FD>& out);
void getOutput(int& option, std::string& file);

// Misc
void outputToFile(std::string file, std::string val);

// Input
bool extractRelation(std::string input, Relation& out);
bool extractFDs(std::string input, std::vector<FD>& out);
bool extractFD(std::string fd, std::string& left, std::string& right);
std::string removeSpaces(std::string input);