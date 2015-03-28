#include "ThirdNF.h"
#include "ChaseTest.h"
#include "Utils.h"

ThirdNF::ThirdNF()
{
	m_Primes = "";
	m_IsValid = false;
}

ThirdNF::~ThirdNF()
{

}

bool ThirdNF::testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds)
{
	ChaseTest test;

	return test.testNormalization(origRel, newRels, fds);
}

void ThirdNF::normalize(Relation relation, const std::vector<FD>& fds)
{
	//find the number of attributes in the relation
	int relationLength = relation.attributes.size();

	//search for permutations
	for (int i = 0; i < relationLength; ++i)
	{
		ClosureSet* newSet;
		newSet = findClosureSet(relation, i + 1);
		m_ClosureSets.push_back(newSet);
	}

	calculateClosureRightSide(m_ClosureSets, fds);
	extractClosureKeys(relation, m_ClosureSets, m_Keys, m_SuperKeys);
	extractClosureFDs(m_ClosureSets, m_ClosureFDs);
	calculateSetOfPrimes(m_Keys, m_Primes);

	calculateFDViolations(m_ClosureFDs, m_Primes, m_Keys, m_FDViolations);

	getMinimalBasis(fds, m_NewFds);
	createRelationsFromMinimalBasis(m_NewFds, m_NewRelations);
	eliminateSubsetRelations(m_NewRelations);
	
	// If none of the relations contain a key in their schema, we will add a new relation that does
	if (!checkIfRelationsContainKey(m_NewRelations, m_Keys))
	{
		Relation rel(m_Keys[0]);
		m_NewRelations.push_back(rel);
	}

	m_IsValid = testNormalization(relation, m_NewRelations, fds);
}

std::string ThirdNF::getResults()
{
	return "";
}

void ThirdNF::calculateFDViolations(const std::vector<FD>& closureFds, const std::string& primes, const std::vector<std::string>& keys, std::vector<FD>& violations)
{
	for (unsigned int i = 0; i < closureFds.size(); i++)
	{
		if (Utils::stringContainsChars(primes, closureFds[i].right))
			continue;

		bool valid = false;
		for (unsigned int j = 0; j < keys.size(); j++)
		{
			if (Utils::stringContainsChars(closureFds[i].left, keys[j]))
			{
				valid = true;
				break;
			}
		}

		if (!valid)
			violations.push_back(FD(closureFds[i]));
	}
}

void ThirdNF::calculateClosureRightSide(std::vector<ClosureSet*>& closures, const std::vector<FD>& fds)
{
	for (unsigned int i = 0; i < closures.size(); i++)
	{
		std::vector<Permutation> perms = closures[i]->getPermutations();

		for (unsigned int j = 0; j < perms.size(); j++)
		{
			for (unsigned int k = 0; k < fds.size(); k++)
			{
				if (Utils::stringContainsChars(perms[j].getRightSide(), fds[k].left))
				{
					closures[i]->addToPermRight(j, fds[k].right);
				}
			}
		}
	}
}

void ThirdNF::extractClosureKeys(Relation origRel, const std::vector<ClosureSet*>& closures, std::vector<std::string>& keys, std::vector<std::string>& superKeys)
{
	int keyFound = -1;

	for (unsigned int i = 0; i < closures.size(); i++)
	{
		std::vector<Permutation> perms = closures[i]->getPermutations();

		for (unsigned int j = 0; j < perms.size(); j++)
		{
			if (Utils::stringContainsChars(perms[j].getRightSide(), origRel.attributes))
			{
				if (keyFound == -1 || keyFound == i)
				{
					keyFound = i;
					keys.push_back(perms[j].getAttributes());
				}
				else
					superKeys.push_back(perms[j].getAttributes());
			}
		}
	}
}

void ThirdNF::extractClosureFDs(const std::vector<ClosureSet*>& closures, std::vector<FD>& closureFds)
{
	std::vector<FD> tempFds;

	// Finds all the FDs from the closure sets
	for (unsigned int i = 0; i < closures.size(); i++)
	{
		std::vector<Permutation> perms = closures[i]->getPermutations();

		for (unsigned int j = 0; j < perms.size(); j++)
		{
			if (perms[j].getAttributeSize() == perms[j].getRightSize())
				continue;

			tempFds.push_back(FD(perms[j].getAttributes(), Utils::stringSubtract(perms[j].getRightSide(), perms[j].getAttributes())));
		}
	}

	// Makes sure the right side only has 1 value
	for (unsigned int i = 0; i < tempFds.size(); i++)
	{
		if (tempFds[i].right.size() == 1)
			closureFds.push_back(FD(tempFds[i]));
		else
		{
			for (unsigned int j = 0; j < tempFds[i].right.size(); j++)
			{
				closureFds.push_back(FD(tempFds[i].left, Utils::convertToString<char>(tempFds[i].right[j])));
			}
		}
	}
}

void ThirdNF::calculateSetOfPrimes(const std::vector<std::string>& keys, std::string& primes)
{
	bool exists = false;
	for (unsigned int i = 0; i < keys.size(); i++)
	{
		for (unsigned int j = 0; j < keys[i].size(); j++)
		{
			for (unsigned int k = 0; k < primes.size(); k++)
			{
				if (keys[i][j] == primes[k])
				{
					exists = true;
					break;
				}
			}

			if (!exists)
			{
				primes += keys[i][j];
			}
		}
	}
}

void ThirdNF::getMinimalBasis(const std::vector<FD>& oldFds, std::vector<FD>& newFds)
{
	// Add all the oldFds to the newFds and make sure the right hand side only has 1 value
	for (unsigned int i = 0; i < oldFds.size(); i++)
	{
		if (oldFds[i].right.size() == 1)
			newFds.push_back(FD(oldFds[i]));
		else
		{
			for (unsigned int j = 0; j < oldFds[i].right.size(); j++)
			{
				newFds.push_back(FD(oldFds[i].left, Utils::convertToString<char>(oldFds[i].right[j])));
			}
		}
	}

	// Remove all trivial FDs (where something determines itself)
	std::vector<FD>::iterator it = newFds.begin();

	for (it; it != newFds.end(); it++)
	{
		if (Utils::stringContainsChars(it->left, it->right))
		{
			it = newFds.erase(it);
		}
	}

	// Remove redundant FDs
	std::string rightSide = "";

	for (it = newFds.begin(); it != newFds.end(); it++)
	{
		if (Utils::stringContainsChars(rightSide, it->right))
		{
			it = newFds.erase(it);
		}
		else
		{
			rightSide += it->right;
		}
	}
}

void ThirdNF::createRelationsFromMinimalBasis(const std::vector<FD>& fds, std::vector<Relation>& rels)
{
	for (unsigned int i = 0; i < fds.size(); i++)
	{
		Relation rel;
		rel += fds[i].left;
		rel += fds[i].right;
		
		rels.push_back(rel);
	}
}

void ThirdNF::eliminateSubsetRelations(std::vector<Relation>& rels)
{
	// Find the relations that are subsets of other relations and delete them
	for (unsigned int i = 0; i < rels.size(); i++)
	{
		for (unsigned int j = 0; j < rels.size(); j++)
		{
			// Skip ourselves
			if (i == j)
				continue;

			// If i is a subset of j, remove i
			if (Utils::stringContainsChars(rels[j].attributes, rels[i].attributes))
			{
				rels.erase(rels.begin() + i);
				i--;
				break;
			}
		}
	}
}

bool ThirdNF::checkIfRelationsContainKey(std::vector<Relation>& rels, const std::vector<std::string>& keys)
{
	for (unsigned int i = 0; i < rels.size(); i++)
	{
		for (unsigned int j = 0; j < keys.size(); j++)
		{
			if (Utils::stringContainsChars(rels[i].attributes, keys[j]))
			{
				return true;
			}
		}
	}

	return false;
}