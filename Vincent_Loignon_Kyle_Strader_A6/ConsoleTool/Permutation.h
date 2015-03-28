#pragma once

#include<vector>

struct Permutation
{
public:
	//Constructors/Destructors
	Permutation() { permutation = ""; rightSide = ""; }
	Permutation(std::string atts) { permutation = atts; rightSide = atts; }
	Permutation(char att) { permutation = att; rightSide = att; }
	~Permutation() {}

	//Utils
	char getAttribute(int iter) { return permutation[iter]; }
	std::string getAttributes() { return permutation; }
	std::string getRightSide() { return rightSide; }
	int getAttributeSize() { return permutation.size(); }
	int getRightSize() { return rightSide.size(); }
	void insertAttributes(std::string att, int iter) { permutation.insert(iter, att); rightSide.insert(iter, att); }
	void insertRightSide(std::string att, int iter) { rightSide.insert(iter, att); }

	void addToRight(std::string right)
	{
		bool exists = false;
		for (unsigned int i = 0; i < right.size(); i++)
		{
			for (unsigned int j = 0; j < rightSide.size(); j++)
			{
				if (right[i] == rightSide[j])
				{
					exists = true;
					break;
				}
			}

			if (!exists)
			{
				rightSide += right[i];
			}
		}
	}

	//Operator Overloads
	void operator+=(std::string att)
	{
		permutation += att;
		rightSide += att;
	}

	void operator+=(Permutation perm)
	{
		permutation += perm.getAttributes();
		rightSide += perm.getAttributes();
	}

	Permutation operator+(std::string att)
	{
		return Permutation(permutation += att);
	}

	Permutation operator+(Permutation perm)
	{
		return Permutation(permutation + perm.getAttributes());
	}

private: 
	std::string permutation;
	std::string rightSide;
};

