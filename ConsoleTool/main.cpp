#include "main.h"

#include "ChaseTest.h"
#include "ThirdNF.h"
#include "Relation.h"
#include "FD.h"

int main()
{
	printf("Welcome to Kyle & Vince's DBMS Console Tool!\n");

	ChaseTest test;
	ThirdNF thirdNF;
	Relation origRel("ABCDE");
	std::vector<Relation> newRels;
	std::vector<FD> fds;

	newRels.push_back(Relation("AB"));
	newRels.push_back(Relation("BCD"));
	newRels.push_back(Relation("ACE"));

	fds.push_back(FD("A", "B"));
	fds.push_back(FD("BC", "D"));
	fds.push_back(FD("AC", "E"));

	thirdNF.normalize(origRel, fds);
	test.testNormalization(origRel, newRels, fds);

	system("pause");
	return 0;
}