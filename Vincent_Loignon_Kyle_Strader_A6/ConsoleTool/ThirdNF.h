#pragma once

#include "NormalForm.h"

class ThirdNF : public NormalForm
{
protected:
	bool testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds); // Returns true if its valid, false otherwise

private:
	std::vector<ClosureSet*> m_ClosureSets;
	std::vector<FD> m_ClosureFDs;
	std::vector<FD> m_BaseFds;
	std::vector<FD> m_NewFds;
	Relation m_BaseRelation;
	std::vector<Relation> m_BaseRelations;
	std::vector<Relation> m_SubsetRemovedRelations;
	std::vector<Relation> m_NewRelations;
	std::vector<std::string> m_Keys;
	std::vector<std::string> m_SuperKeys;
	std::vector<FD> m_FDViolations;
	std::string m_Primes;
	bool m_IsValid;
	
	void calculateFDViolations(const std::vector<FD>& closureFds, const std::string& primes, const std::vector<std::string>& keys, std::vector<FD>& violations);
	void calculateSetOfPrimes(const std::vector<std::string>& keys, std::string& primes);
	void extractClosureFDs(const std::vector<ClosureSet*>& closures, std::vector<FD>& closureFds);
	void extractClosureKeys(Relation origRel, const std::vector<ClosureSet*>& closures, std::vector<std::string>& keys, std::vector<std::string>& superKeys);
	void calculateClosureRightSide(std::vector<ClosureSet*>& closures, const std::vector<FD>& fds);
	void getMinimalBasis(const std::vector<FD>& oldFds, std::vector<FD>& newFds);
	void createRelationsFromMinimalBasis(const std::vector<FD>& fds, std::vector<Relation>& rels);
	void eliminateSubsetRelations(std::vector<Relation>& rels);
	bool checkIfRelationsContainKey(std::vector<Relation>& rels, const std::vector<std::string>& keys);

public:
	ThirdNF();
	~ThirdNF();

	void normalize(Relation relation, const std::vector<FD>& fds); // Starts the normalization algorithm defined by the derived class
	std::string getResults(); // Returns the formatted results as a string
};