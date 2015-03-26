#pragma once

#include"Permutation.h"

struct ClosureSet
{
public:
	//Constructors/Destructors
	ClosureSet(){};
	~ClosureSet(){};
	
	//Utils
	Permutation getAttribute(int iter) { return closureSet.at(iter); };
	int getSize() { return closureSet.size(); };
	int getClosureMaxSize() { return closureSize; };

	//Operator Overloads
	void operator+=(Permutation perm)
	{
		closureSet.push_back(perm);
	}

private: 
	std::vector<Permutation> closureSet;
	int closureSize;
};

