#pragma once

#include"Permutation.h"

struct ClosureSet
{
public:
	//Constructors/Destructors
	ClosureSet(){}
	ClosureSet(std::vector<Permutation> set){ closureSet = set; }
	ClosureSet(Permutation perm){ closureSet.push_back(perm); }
	~ClosureSet(){}
	
	//Utils
	Permutation getAttribute(int iter) { return closureSet.at(iter); }
	std::vector<Permutation>& getPermutations() { return closureSet; } // Don't use this if you want to modify the perms!
	Permutation getPerm(int i) { return closureSet[i]; }
	int getSize() { return closureSet.size(); }
	bool addToPermRight(int perm, std::string right) { return closureSet[perm].addToRight(right); }

	//Operator Overloads
	void operator+=(Permutation perm)
	{
		closureSet.push_back(perm);
	}

	void operator+=(ClosureSet set)
	{
		std::vector<Permutation> tmpSet = set.getPermutations();
		closureSet.insert(closureSet.end(), tmpSet.begin(), tmpSet.end());
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
};