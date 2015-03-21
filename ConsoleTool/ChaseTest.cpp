#include "ChaseTest.h"
#include "Relation.h"
#include "FD.h"
#include "Utils.h"
#include <utility>

ChaseTest::ChaseTest()
{

}

ChaseTest::~ChaseTest()
{

}

bool ChaseTest::testNormalization(Relation* origRel, std::vector<Relation*>& newRels, std::vector<FD*>& fds)
{
	populateTable(origRel, newRels);
	modifyTableForFD(fds);
	return isTableValid(origRel);
}

void ChaseTest::populateTable(Relation* origRel, std::vector<Relation*>& relations)
{
	// Fill the map with the proper keys and resize the tables as we do this
	for (unsigned int i = 0; i < origRel->attributes.size(); i++)
	{
		std::vector<std::string> vec;
		vec.resize(relations.size(), "");

		m_Table[Utils::convertToString<char>(origRel->attributes[i])] = vec;
	}

	// Populate the table with values from the relations
	for (unsigned int i = 0; i < origRel->attributes.size(); i++)
	{
		std::string curAtt = Utils::convertToString<char>(origRel->attributes[i]);
		for (unsigned int j = 0; j < relations.size(); j++)
		{
			for (unsigned int k = 0; k < relations[j]->attributes.size(); k++)
			{
				// If the current relation has the same attribute we are looking for, right it down
				if (relations[j]->attributes[k] == origRel->attributes[i])
				{
					m_Table[curAtt][j] = relations[j]->attributes[k];
					break;
				}
			}

			// If the relation didn't have that attribute, add a temp one with the row number attached
			if (m_Table[curAtt][j] == "")
				m_Table[curAtt][j] = curAtt + Utils::convertToString<int>(j + 1);
		}
	}
}

void ChaseTest::modifyTableForFD(std::vector<FD*>& fds)
{
	for (unsigned int i = 0; i < fds.size(); i++)
	{
		std::vector<std::pair<std::string, std::vector<int>>> keys;

		// Grab all the keys from the table that the fd is using
		for (unsigned int j = 0; j < fds[i]->left.size(); j++)
		{
			std::string key = findKey(Utils::convertToString<char>(fds[i]->left[j]));

			if (key == "")
				continue;
			
			std::vector<int> temp;

			keys.push_back(std::make_pair(key, temp));
		}

		// Find all the values that are appropriate across all keys
		for (unsigned int j = 0; j < keys.size(); j++)
		{
			for (unsigned int k = 0; k < m_Table[keys[j].first].size(); k++)
			{
				// If the value in this spot is the same as the key, write down the index
				if (m_Table[keys[j].first][k] == keys[j].first)
					keys[j].second.push_back(k);
			}
		}

		std::vector<int> pairs;

		// Find pairs
		for (unsigned int j = 0; j < keys[0].second.size(); j++)
		{
			bool valid = true;

			for (unsigned int k = 1; k < keys.size(); k++)
			{
				// If the key doesn't have this index, the pair isn't possible for this index
				if (!findValue(keys[k].second, keys[0].second[j]))
				{
					valid = false;
					break;
				}
			}

			if (valid)
				pairs.push_back(keys[0].second[j]);
		}

		std::string newVal = "";

		// Find the "highest" value to change to from the pairs
		for (unsigned int j = 0; j < pairs.size(); j++)
		{
			std::string val = m_Table[fds[i]->right][pairs[j]];
			
			if (newVal == "")
				newVal = val;
			else
			{
				if (val.size() < newVal.size())
					newVal = val;
				else
				{
					int num1 = Utils::convertToInt<std::string>(val.substr(1, val.size() - 1));
					int num2 = Utils::convertToInt<std::string>(newVal.substr(1, newVal.size() - 1));

					if (num1 < num2)
						newVal = val;
				}
			}
		}

		// Change the right hand side key's values from the pairs to the highest value
		for (unsigned int j = 0; j < pairs.size(); j++)
		{
			m_Table[fds[i]->right][pairs[j]] = newVal;
		}
	}
}

std::string ChaseTest::findKey(std::string value)
{
	std::map<std::string, std::vector<std::string>>::iterator it = m_Table.find(value);

	if (it == m_Table.end())
		return "";
	else
		return it->first;
}

bool ChaseTest::findValue(std::vector<int>& list, int value)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i] == value)
			return true;
	}

	return false;
}

bool ChaseTest::isTableValid(Relation* origRel)
{
	std::vector<int> validIndexs;

	std::string key = findKey(Utils::convertToString<char>(origRel->attributes[0]));

	// find all the valid indexes
	for (unsigned int i = 0; i < m_Table[key].size(); i++)
	{
		std::string iVal = m_Table[key][i];

		if (iVal != key)
			continue;

		validIndexs.push_back(i);
	}

	// Don't even continue if there are no valid indexes at the start
	if (validIndexs.size() == 0)
		return false;

	// Iterate through each of the valid indexes, we will search for them 1 by 1
	for (unsigned int i = 0; i < validIndexs.size(); i++)
	{
		bool valid = true;

		// Iterate through the rest of the keys (kind of like a DFS) and skip them if they don't have the value
		for (unsigned int j = 1; j < origRel->attributes.size(); j++)
		{
			key = findKey(Utils::convertToString<char>(origRel->attributes[j]));

			if (m_Table[key][validIndexs[i]] != key)
			{
				valid = false;
				break;
			}
		}

		if (valid)
			return true;
	}

	return false;
}