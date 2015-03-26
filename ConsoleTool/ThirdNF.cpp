#include "ThirdNF.h"
#include "ChaseTest.h"

ThirdNF::ThirdNF()
{

}

ThirdNF::~ThirdNF()
{

}

bool ThirdNF::testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds)
{
	ChaseTest test;

	return test.testNormalization(origRel, newRels, fds);
}

void ThirdNF::normalize(Relation* relation, std::vector<FD*> fds)
{
	std::vector<ClosureSet*> ClosureSets;
	
	//find the number of attributes in the relation
	int relationLength = relation->attributes.size();

	//search for permutations
	for (int i = 0; i < relationLength; ++i)
	{
		ClosureSet* newSet = new ClosureSet();
		findClosureSet(newSet, relation, i + 1, 0);
		ClosureSets.push_back(newSet);
	}
}

std::string ThirdNF::getResults()
{
	return "";
}