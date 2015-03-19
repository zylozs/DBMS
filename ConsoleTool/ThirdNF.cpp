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

}

std::string ThirdNF::getResults()
{
	return "";
}