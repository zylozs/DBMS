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
	int getSize() { return permutation.size(); };
	void insertAttributes(std::string att, int iter) { permutation.insert(iter, att); };

	//Operator Overloads
	void operator+=(std::string att)
	{
		permutation += att;
	}

private: 
	std::string permutation;
};

