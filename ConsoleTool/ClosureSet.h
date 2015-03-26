#pragma once

#include"Permutation.h"

struct ClosureSet
{
public:
	//Constructors/Destructors
	ClosureSet(){};
	ClosureSet(std::vector<Permutation> set){ closureSet = set; };
	~ClosureSet(){};
	
	//Utils
	Permutation getAttribute(int iter) { return closureSet.at(iter); };
	std::vector<Permutation> getPermutations() { return closureSet; };
	int getSize() { return closureSet.size(); };
	int getClosureMaxSize() { return closureSize; };

	//Operator Overloads
	void operator+=(Permutation perm)
	{
		closureSet.push_back(perm);
	}

	void operator+=(ClosureSet set)
	{
		closureSet.insert(closureSet.end(), set.getPermutations().begin(), set.getPermutations().end());
	}

	ClosureSet operator+(Permutation perm)
	{
		std::vector<Permutation> tmp = closureSet;
		tmp.push_back(perm);
		return ClosureSet(tmp);
	}

	ClosureSet operator+(ClosureSet set)
	{
		std::vector<Permutation> tmp = closureSet;
		tmp.insert(tmp.end(), set.getPermutations().begin(), set.getPermutations().end());
		return ClosureSet(tmp);
	}

private: 
	std::vector<Permutation> closureSet;
	int closureSize;
};

