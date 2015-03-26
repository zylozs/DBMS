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
	std::vector<ClosureSet> ClosureSets;

	//find the number of attributes in the relation
	int relationLength = relation.attributes.size();

	//search for permutations
	for (int i = 0; i < relationLength; ++i)
	{
		ClosureSet newSet;
		findClosureSet(relation, i + 1);
		ClosureSets.push_back(newSet);
	}

	std::vector<FD> newFds;

	getMinimalBasis(fds, newFds);
}

std::string ThirdNF::getResults()
{
	return "";
}

void ThirdNF::getMinimalBasis(const std::vector<FD>& oldFds, std::vector<FD>& newFds)
{
	for (int i = 0; i < oldFds.size(); i++)
	{
		if (oldFds[i].right.size() == 1)
			newFds.push_back(FD(oldFds[i]));
		else
		{
			for (int j = 0; j < oldFds[i].right.size(); j++)
			{
				newFds.push_back(FD(oldFds[i].left, Utils::convertToString<char>(oldFds[i].right[j])));
			}
		}
	}
}