#pragma once

#include <string>

struct FD
{
	std::string left; // Use single letters for each attribute for simplicity
	std::string right; // Use single letters for each attribute for simplicity

	FD(std::string l = "", std::string r = "")
	{
		left = l;
		right = r;
	}
};