#pragma once

#include <string>
#include <vector>

#include "Permutation.h"
#include "ClosureSet.h"
#include "Relation.h"
#include "FD.h"

class NormalForm
{
protected:
	virtual bool testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds) = 0; // Returns true if its valid, false otherwise

public:
	NormalForm() {}
	~NormalForm() {}

	virtual void normalize(Relation relation, const std::vector<FD>& fds) = 0; // Starts the normalization algorithm defined by the derived class
	virtual std::string getResults() = 0; // Returns the formatted results as a string
	ClosureSet findClosureSet(Relation rel, int closureSize);
	ClosureSet findPermutations(Permutation prefix, Relation rel, int closureSize);
};