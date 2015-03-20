#include "ChaseTest.h"
#include "Relation.h"
#include "FD.h"
#include "Utils.h"

ChaseTest::ChaseTest()
{

}

ChaseTest::~ChaseTest()
{

}

bool ChaseTest::testNormalization(Relation* origRel, std::vector<Relation*> newRels, std::vector<FD*> fds)
{
	populateTable(origRel, newRels);

	return false;
}

void ChaseTest::populateTable(Relation* origRel, std::vector<Relation*> relations)
{
	// Resize the table
	m_Table.resize(origRel->attributes.size());

	for (int i = 0; i < m_Table.size(); i++)
	{
		m_Table[i].resize(relations.size());
	}

	// Clear the table 
	for (int i = 0; i < m_Table.size(); i++)
	{
		for (int j = 0; j < m_Table[i].size(); j++)
		{
			m_Table[i][j] = "";
		}
	}

	// Populate the table with values from the relations
	for (int i = 0; i < origRel->attributes.size(); i++)
	{
		for (int j = 0; j < relations.size(); j++)
		{
			for (int k = 0; k < relations[j]->attributes.size(); k++)
			{
				// If the current relation has the same attribute we are looking for, right it down
				if (relations[j]->attributes[k] == origRel->attributes[i])
				{
					m_Table[i][j] = relations[j]->attributes[k];
					break;
				}
			}

			// If the relation didn't have that attribute, add a temp one with the row number attached
			if (m_Table[i][j] == "")
				m_Table[i][j] = origRel->attributes[i] + Utils::convertToString<int>(j + 1);
		}
	}
}