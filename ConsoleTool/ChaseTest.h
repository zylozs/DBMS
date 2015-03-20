#pragma once

#include <vector>

struct Relation;
struct FD;

class ChaseTest
{
protected:
	std::vector<std::vector<std::string>> m_Table; // The data table we create

	void populateTable(Relation* origRel, std::vector<Relation*> relations);

public:
	ChaseTest();
	~ChaseTest();

	bool testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds);
};