#include "ThirdNF.h"
#include "ChaseTest.h"
#include "Utils.h"

ThirdNF::ThirdNF()
{

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

	getMinimalBasis(fds, m_NewFds);
	createRelationsFromMinimalBasis(m_NewFds, m_NewRelations);
	eliminateSubsetRelations(m_NewRelations);
	
	// If none of the relations contain a key in their schema, we will add a new relation that does
	if (!checkIfRelationsContainKey(m_NewRelations, m_Keys))
	{
		Relation rel(m_Keys[0].left);
		m_NewRelations.push_back(rel);
	}
}

std::string ThirdNF::getResults()
{
	return "";
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
		if (Utils::stringContains(it->left, it->right))
		{
			it = newFds.erase(it);
		}
	}

	// Remove redundant FDs
	std::string rightSide = "";

	for (it = newFds.begin(); it != newFds.end(); it++)
	{
		if (Utils::stringContains(rightSide, it->right))
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
			if (Utils::stringContains(rels[j].attributes, rels[i].attributes))
			{
				rels.erase(rels.begin() + i);
				i--;
				break;
			}
		}
	}
}

bool ThirdNF::checkIfRelationsContainKey(std::vector<Relation>& rels, const std::vector<FD>& keys)
{
	for (unsigned int i = 0; i < rels.size(); i++)
	{
		for (unsigned int j = 0; j < keys.size(); j++)
		{
			if (Utils::stringContains(rels[i].attributes, keys[j].left))
			{
				return true;
			}
		}
	}

	return false;
}