#include "main.h"

#include "ChaseTest.h"
#include "Relation.h"
#include "FD.h"

int main()
{
	printf("Welcome to Kyle & Vince's DBMS Console Tool!\n");

	ChaseTest test;
	Relation* origRel = new Relation("ABCDE");
	std::vector<Relation*> newRels;
	std::vector<FD*> fds;

	newRels.push_back(new Relation("ABC"));
	newRels.push_back(new Relation("AD"));
	newRels.push_back(new Relation("ABE"));

	fds.push_back(new FD("AB", "C"));
	fds.push_back(new FD("C", "B"));
	fds.push_back(new FD("A", "D"));

	test.testNormalization(origRel, newRels, fds);

	system("pause");
	return 0;
}