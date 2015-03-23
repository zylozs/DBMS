#pragma once

#include <string>
#include <vector>

#include "Relation.h"
#include "FD.h"

class NormalForm
{
protected:
	virtual bool testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds) = 0; // Returns true if its valid, false otherwise

public:
	NormalForm() {}
	~NormalForm() {}

	virtual void normalize(Relation* relation, std::vector<FD*> fds) = 0; // Starts the normalization algorithm defined by the derived class
	virtual std::string getResults() = 0; // Returns the formatted results as a string
};