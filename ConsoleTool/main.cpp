#include "main.h"

#include "ChaseTest.h"
#include "Relation.h";
#include "FD.h"

int main()
{
	printf("Welcome to Kyle & Vince's DBMS Console Tool!\n");

	ChaseTest test;
	Relation* origRel = new Relation("ABCDE");
	std::vector<Relation*> newRels;
	std::vector<FD*> fds;

	newRels.push_back(new Relation("AB"));
	newRels.push_back(new Relation("BCD"));
	newRels.push_back(new Relation("ACE"));

	fds.push_back(new FD("A", "B"));
	fds.push_back(new FD("BC", "D"));
	fds.push_back(new FD("AC", "E"));

	test.testNormalization(origRel, newRels, fds);

	system("pause");
	return 0;
}