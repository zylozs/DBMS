#pragma once

#include "NormalForm.h"

class ThirdNF : public NormalForm
{
protected:
	virtual bool testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds); // Returns true if its valid, false otherwise

public:
	ThirdNF();
	~ThirdNF();

	virtual void normalize(Relation* relation, std::vector<FD*> fds); // Starts the normalization algorithm defined by the derived class
	virtual std::string getResults(); // Returns the formatted results as a string
};