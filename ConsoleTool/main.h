#pragma once

#include <iostream>
#include "ChaseTest.h"
#include "ThirdNF.h"
#include "Relation.h"
#include "FD.h"
#include "Utils.h"

bool extractRelation(std::string input, Relation& out);
bool extractFDs(std::string input, std::vector<FD>& out);
bool extractFD(std::string fd, std::string& left, std::string& right);
std::string removeSpaces(std::string input);