#pragma once

#include <vector>
#include <map>

struct Relation;
struct FD;

class ChaseTest
{
protected:
	std::map<std::string, std::vector<std::string>> m_Table; // The data table we create

	std::string findKey(std::string value);
	bool findValue(std::vector<int>& list, int value);

	void populateTable(Relation* origRel, std::vector<Relation*>& relations);
	void modifyTableForFD(std::vector<FD*>& fds);
	bool isTableValid(Relation* origRel);

public:
	ChaseTest();
	~ChaseTest();

	bool testNormalization(Relation* origRel, std::vector<Relation*>& newRels, std::vector<FD*>& fds);
};