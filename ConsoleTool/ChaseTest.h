#pragma once

#include <vector>
#include <map>

struct Relation;
struct FD;

class ChaseTest
{
protected:
	std::map<std::string, std::vector<std::string>> m_Table; // The data table we create
	std::map<std::string, std::vector<std::string>> m_BaseTable;

	std::string findKey(std::string value);
	bool findValue(const std::vector<int>& list, int value);

	void populateTable(Relation origRel, const std::vector<Relation>& relations);
	void modifyTableForFD(const std::vector<FD>& fds);
	bool isTableValid(Relation origRel);

public:
	ChaseTest();
	~ChaseTest();

	std::map<std::string, std::vector<std::string>> getTable() { return m_Table; };
	std::map<std::string, std::vector<std::string>> getBaseTable() { return m_BaseTable; };

	bool testNormalization(Relation origRel, const std::vector<Relation>& newRels, const std::vector<FD>& fds);
};