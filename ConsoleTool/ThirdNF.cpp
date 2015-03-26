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
	std::vector<std::vector<std::vector<char>*>*>* permutations = new std::vector<std::vector<std::vector<char>*>*>;
	//!DELETE!//
	std::vector<char>* attributes = parseAttributeStr(relation->attributes); 
	//!DELETE!//
	
	//find the number of attributes in the relation
	int relationLength = attributes->size();

	//search for permutations
	for (int i = 0; i < relationLength; ++i)
	{
		permutations->push_back(findPermutations(attributes, i + 1, 0, relationLength));
	}

	return;
}

//this function allocates memory!
std::vector<char>* ThirdNF::parseAttributeStr(std::string attrs)
{
	//convert the attributes string into a dynamically allocated character pointer
	char *relChars = (char*)attrs.c_str();
	//convert the character pointer into a vector
	std::vector<char>* attributes = new std::vector<char>;

	int numAttributes = std::strlen(relChars);
	for (int i = 0; i < numAttributes; ++i)
	{
		attributes->push_back(relChars[i]);
	}

	return attributes;
}

//this function allocates memory!
std::vector<std::vector<char>*>* ThirdNF::findPermutations(std::vector<char>* relation, int closureSize, int startIter, int relationSize)
{
	//!DELETE!//
	std::vector<std::vector<char>*>* permutations = new std::vector<std::vector<char>*>;
	//!DELETE!//
	if (closureSize > 0)
	{
		for (int i = startIter; i < relationSize; ++i)
		{
			for (int j = i + 1; j + closureSize < relationSize; ++j)
			{
				std::vector<char>* permutation = new std::vector<char>;
				permutation->push_back(relation->at(i));
				std::vector<char>* tmpPerm = detailPermutation(relation, closureSize - 1, j, relationSize);
				permutation->insert(permutation->end(), tmpPerm->begin(), tmpPerm->end());
				delete tmpPerm;
				permutations->push_back(permutation);
			}
		}
	}
	return permutations;
}

std::vector<char>* ThirdNF::detailPermutation(std::vector<char>* relation, int closureSize, int startIter, int relationSize)
{
	std::vector<char>* permutation = new std::vector<char>;
	permutation->push_back(relation->at(startIter));
	std::vector<char>* tmpPerm = detailPermutation(relation, closureSize - 1, startIter + 1, relationSize);
	permutation->insert(permutation->end(), tmpPerm->begin(), tmpPerm->end());
	delete tmpPerm;
	return permutation;
}

std::string ThirdNF::getResults()
{
	return "";
}