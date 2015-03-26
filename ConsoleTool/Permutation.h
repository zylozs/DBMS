#pragma once

#include<vector>

struct Permutation
{
public:
	//Constructors/Destructors
	Permutation() { permutation = ""; };
	Permutation(std::string atts) { permutation = atts; };
	Permutation(char att) { permutation = att; };
	~Permutation() {};

	//Utils
	char getAttribute(int iter) { return permutation[iter]; };
	std::string getAttributes() { return permutation; };
	int getSize() { return permutation.size(); };
	void insertAttributes(std::string att, int iter) { permutation.insert(iter, att); };

	//Operator Overloads
	void operator+=(std::string att)
	{
		permutation += att;
	}

	void operator+=(Permutation perm)
	{
		permutation += perm.getAttributes();
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
};

