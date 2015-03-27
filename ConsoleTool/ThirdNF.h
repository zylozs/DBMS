#pragma once

#include "NormalForm.h"

class ThirdNF : public NormalForm
{
protected:
	bool testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds); // Returns true if its valid, false otherwise

private:
	std::vector<ClosureSet*> m_ClosureSets;
	std::vector<FD> m_NewFds;
	std::vector<FD> m_ClosureFDs;
	std::vector<Relation> m_NewRelations;
	std::vector<FD> m_Keys;

	void getMinimalBasis(const std::vector<FD>& oldFds, std::vector<FD>& newFds);
	void createRelationsFromMinimalBasis(const std::vector<FD>& fds, std::vector<Relation>& rels);
	void eliminateSubsetRelations(std::vector<Relation>& rels);
	bool checkIfRelationsContainKey(std::vector<Relation>& rels, const std::vector<FD>& keys);

public:
	ThirdNF();
	~ThirdNF();

	void normalize(Relation relation, const std::vector<FD>& fds); // Starts the normalization algorithm defined by the derived class
	std::string getResults(); // Returns the formatted results as a string
};