#pragma once

#include <vector>

struct Relation;
struct FD;

class ChaseTest
{
public:
	ChaseTest();
	~ChaseTest();

	bool testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds);
};