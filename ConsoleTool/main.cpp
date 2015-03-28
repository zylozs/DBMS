#include "main.h"

#include "ChaseTest.h"
#include "ThirdNF.h"
#include "Relation.h"
#include "FD.h"
#include "Utils.h"

int main()
{
	printf("Welcome to Kyle & Vince's DBMS Console Tool!\n");

	ChaseTest test;
	ThirdNF thirdNF;
	Relation origRel("ABCD");
	std::vector<Relation> newRels;
	std::vector<FD> fds;

	newRels.push_back(Relation("BC"));
	newRels.push_back(Relation("BD"));
	newRels.push_back(Relation("AB"));

	fds.push_back(FD("B", "C"));
	fds.push_back(FD("B", "D"));

	thirdNF.normalize(origRel, fds);
	//test.testNormalization(origRel, newRels, fds);

	system("pause");
	return 0;
}