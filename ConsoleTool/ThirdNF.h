#pragma once

#include "NormalForm.h"

class ThirdNF : public NormalForm
{
protected:
	bool testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds); // Returns true if its valid, false otherwise

private:
	void getMinimalBasis(const std::vector<FD>& oldFds, std::vector<FD>& newFds);

public:
	ThirdNF();
	~ThirdNF();

	void normalize(Relation relation, const std::vector<FD>& fds); // Starts the normalization algorithm defined by the derived class
	std::string getResults(); // Returns the formatted results as a string
};