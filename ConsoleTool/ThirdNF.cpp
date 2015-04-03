#include "ThirdNF.h"
#include "ChaseTest.h"
#include "Utils.h"
#include <iostream>
#include "OutputUtils.h"
#include <sstream>

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
	return m_Test.testNormalization(origRel, newRels, fds);
}

void ThirdNF::normalize(Relation relation, const std::vector<FD>& fds)
{
	//find the number of attributes in the relation
	int relationLength = relation.attributes.size();

	//Store the original FDs
	m_BaseFds = fds;

	//Store the original relation
	m_BaseRelation = relation;

	//search for permutations
	for (int i = 0; i < relationLength; ++i)
	{
		ClosureSet* newSet;
		newSet = findClosureSet(m_BaseRelation, i + 1);
		m_ClosureSets.push_back(newSet);
	}

	calculateClosureRightSide(m_ClosureSets, m_BaseFds);
	extractClosureKeys(m_BaseRelation, m_ClosureSets, m_Keys, m_SuperKeys);
	extractClosureFDs(m_ClosureSets, m_ClosureFDs);
	calculateSetOfPrimes(m_Keys, m_Primes);

	calculateFDViolations(m_ClosureFDs, m_Primes, m_Keys, m_FDViolations);

	getMinimalBasis(m_BaseFds, m_NewFds);
	createRelationsFromMinimalBasis(m_NewFds, m_NewRelations);
	eliminateSubsetRelations(m_NewRelations);
	
	// If none of the relations contain a key in their schema, we will add a new relation that does
	if (!checkIfRelationsContainKey(m_NewRelations, m_Keys))
	{
		Relation rel(m_Keys[0]);
		m_NewRelations.push_back(rel);
	}

	m_IsValid = testNormalization(m_BaseRelation, m_NewRelations, m_BaseFds);
}

std::string ThirdNF::getResults()
{
	std::string result;
	//Empty Line
	result += "\n";

	//Title
	result += "/////////////////////////////\n";
	result += "--3NF Normalization Results--\n";
	result += "/////////////////////////////\n";
	
	//Empty Line
	result += "\n";

	//Original Relation
	result += "-Original Relation-\n\n";
	result += "R(";
	result += OutputUtils::listCharacters(m_BaseRelation.attributes);
	result += ")\n";

	//Original FDs
	result += OutputUtils::listFunctionalDependencies(m_BaseFds);

	//Empty Line
	result += "\n";

	//Closure Results
	result += "-Closure Statements-\n\n";
	unsigned int numClosureSets = m_ClosureSets.size();
	for (unsigned int i = 0; i < numClosureSets; ++i)
	{
		ClosureSet set = *m_ClosureSets.at(i);
		unsigned int numPermutations = set.getPermutations().size();
		for (unsigned int j = 0; j < numPermutations; ++j)
		{
			//Left hand side
			Permutation perm = set.getPermutations().at(j);
			result += "{";

			//--check to see if it is a key or superkey
			unsigned int numKeys = m_Keys.size();
			unsigned int numSuperKeys = m_SuperKeys.size();

			bool isKey = false;
			bool isSuperKey = false;

			for (unsigned int i = 0; i < numKeys; ++i)
			{
				if (perm.getAttributes() == m_Keys.at(i))
				{
					isKey = true;
					break;
				}
			}

			if (!isKey)
			{
				for (unsigned int i = 0; i < numSuperKeys; ++i)
				{
					if (perm.getAttributes() == m_SuperKeys.at(i))
					{
						isSuperKey = true;
						break;
					}
				}
			}
			result += OutputUtils::listCharacters(perm.getAttributes());
			result += "}+ = ";

			//Right hand side
			result += OutputUtils::listCharacters(perm.getRightSide());

			//Is it a key?
			if (isKey)
			{
				result += " - Key";
			}

			if (isSuperKey)
			{
				result += " - SuperKey";
			}

			result += "\n";
		}
	}

	//Empty Line
	result += "\n";

	result += "-Closure Functional Dependencies-\n\n";
	result += OutputUtils::listFunctionalDependencies(m_ClosureFDs);

	//Empty Line
	result += "\n";

	result += "-Minimal Basis Functional Dependencies-\n\n";

	//Check if it is in Minimal Basis
	bool isMinimalBasis = true;

	if (m_BaseFds.size() != m_NewFds.size())
		isMinimalBasis = false;

	if (isMinimalBasis)
	{
		unsigned int numMinimalFDs = m_NewFds.size();
		for (unsigned int i = 0; i < numMinimalFDs; ++i)
		{
			if (m_BaseFds.at(i).left != m_NewFds.at(i).left ||
				m_BaseFds.at(i).right != m_NewFds.at(i).right)
			{
				isMinimalBasis = false;
				break;
			}
		}
	}

	if (isMinimalBasis)
		result += "Is in minimal basis!\n";
	else
		result += "Is not in minimal basis!\n";

	//list the minimal basis FDs
	result += OutputUtils::listFunctionalDependencies(m_NewFds);

	//Empty Line
	result += "\n";

	//List the set of primes
	result += "-Set of Primes-\n\n";
	result += "(";
	result += OutputUtils::listCharacters(m_Primes);
	result += ")\n";

	//Empty Line
	result += "\n";

	//List the set of violations
	result += "-Functional Dependency Violations-\n\n";
	result += OutputUtils::listFunctionalDependencies(m_FDViolations);

	//Empty Line
	result += "\n";

	// If we have no violations, stop here!
	if (m_FDViolations.size() == 0)
		return result;

	//List tables
	result += "-Original Relations-\n\n";
	result += OutputUtils::WriteRelations(m_BaseRelations);

	//Empty Line
	result += "\n";

	//List tables
	result += "-Subset Removed Relations-\n\n";
	result += OutputUtils::WriteRelations(m_SubsetRemovedRelations);

	//Empty Line
	result += "\n";

	//List tables
	result += "-New Relations (after checking for keys)-\n\n";
	result += OutputUtils::WriteRelations(m_NewRelations);

	//Empty Line
	result += "\n";

	//Title
	result += "//////////////\n";
	result += "--Chase Test--\n";
	result += "//////////////\n";

	//Empty Line
	result += "\n";

	result += OutputUtils::WriteTable("R", m_Test.getBaseTable());

	//Empty Line
	result += "\n\n";

	result += OutputUtils::WriteTable("R Modified For FDs", m_Test.getTable());

	//Empty Line
	result += "\n\n";

	//Empty Line
	result += "\n";

	//List tables
	result += "-Chase Test Results-\n\n";
	
	if (m_IsValid)
	{
		result += "Table is valid and lossless!\n";
	}

	else
	{
		result += "Table is NOT valid and is lossy!\n";
	}

	return result;
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
		int numPerms = closures[i]->getSize();
		bool repeatFDs = false;

		for (int j = 0; j < numPerms; j++)
		{
			repeatFDs = false;

			for (unsigned int k = 0; k < fds.size(); k++)
			{
				if (Utils::stringContainsChars(closures[i]->getPerm(j).getRightSide(), fds[k].left))
				{
					bool temp = closures[i]->addToPermRight(j, fds[k].right);

					// If something was actually added, we need to repeat the fds
					if (temp)
						repeatFDs = true;
				}
			}

			// If anything was added to the right side, we repeat the FDs to make sure none are missed
			if (repeatFDs)
				j--;
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
	
	for (unsigned int i = 0; i < keys.size(); i++)
	{
		for (unsigned int j = 0; j < keys[i].size(); j++)
		{
			bool exists = false;
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
	for (unsigned int i = 0; i < newFds.size(); i++)
	{
		if (Utils::stringContainsChars(newFds[i].left, newFds[i].right))
		{
			newFds.erase(newFds.begin() + i);
			i--;
		}
	}

	// Remove redundant FDs
	/*std::string rightSide = "";

	for (unsigned int i = 0; i < newFds.size(); i++)
	{
		if (Utils::stringContainsChars(rightSide, newFds[i].right))
		{
			newFds.erase(newFds.begin() + i);
			i--;
		}
		else
		{
			rightSide += newFds[i].right;
		}
	}*/
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
	m_BaseRelations = rels;
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
	m_SubsetRemovedRelations = rels;
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