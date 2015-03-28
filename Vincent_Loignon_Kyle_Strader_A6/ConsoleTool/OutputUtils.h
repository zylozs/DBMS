#pragma once

#include<vector>
#include "FD.h"

class OutputUtils
{
public:
	OutputUtils(){};
	~OutputUtils(){};

	static std::string listFunctionalDependencies(std::vector<FD> fds)
	{
		std::string result;
		unsigned int numClosureFDs = fds.size();
		for (unsigned int i = 0; i < numClosureFDs; ++i)
		{
			unsigned int attrsLength = fds.at(i).left.size();
			for (unsigned int j = 0; j < attrsLength; ++j)
			{
				if (j + 1 >= attrsLength)
				{
					result += fds.at(i).left[j];
					continue;
				}

				result += fds.at(i).left[j];
				result += ",";
			}

			result += " -> ";

			attrsLength = fds.at(i).right.size();
			for (unsigned int j = 0; j < attrsLength; ++j)
			{
				if (j + 1 >= attrsLength)
				{
					result += fds.at(i).right[j];
					continue;
				}

				result += fds.at(i).right[j];
				result += ",";
			}

			result += "\n";
		}
		return result;
	}

	static std::string listCharacters(std::string chars)
	{
		unsigned int attrsLength = chars.size();
		std::string result;
		for (unsigned int i = 0; i < attrsLength; ++i)
		{
			if (i + 1 >= attrsLength)
			{
				result += chars[i];
				continue;
			}

			result += chars[i];
			result += ",";
		}
		return result;
	}

	static std::string WriteRelation(std::string name, Relation attrs)
	{
		return name + "(" + listCharacters(attrs.attributes) + ")";
	}

	static std::string WriteRelations(std::vector<Relation> rels)
	{
		std::string result;
		unsigned int numRelations = rels.size();
		for (unsigned int i = 0; i < numRelations; ++i)
		{
			std::stringstream ss;
			ss << i + 1;
			std::string num = ss.str();
			result += OutputUtils::WriteRelation("R" + num, rels.at(i));
			result += "\n";
		}

		return result;
	}

	static std::string WriteTable(std::string name, std::map<std::string, std::vector<std::string>> data)
	{
		std::string result;
		result += name + ":\n";

		//find length of longest string
		unsigned int maxStringSize = 0;
		unsigned int maxRows = 0;
		unsigned int maxColumns = data.size();
		std::map<std::string, std::vector<std::string>>::iterator it;
		for (it = data.begin(); it != data.end(); it++)
		{
			std::string val = it->first;
			if (val.size() > maxStringSize)
			{
				maxStringSize = val.size();
			}

			std::vector<std::string> internalVals = it->second;

			if (internalVals.size() > maxRows)
			{
				maxRows = internalVals.size();
			}
			unsigned int numVals = internalVals.size();
			for (unsigned int i = 0; i < numVals; ++i)
			{
				if (internalVals.at(i).size() > maxStringSize)
				{
					maxStringSize = internalVals.at(i).size();
				}
			}
		}

		maxStringSize += 1;

		//Write first line
		for (unsigned int i = 0; i < (maxStringSize * data.size()) + 1 + data.size(); ++i)
		{
			result += "-";
		}

		result += "\n";

		// Write Keys
		std::map<std::string, std::vector<std::string>>::iterator _it;
		for (_it = data.begin(); _it != data.end(); _it++)
		{
			result += "|";
			result += _it->first;
			for (unsigned int i = 0; i < maxStringSize - _it->first.size(); ++i)
			{
				result += " ";
			}
		}

		result += "|\n";

		unsigned int numCharsPerRow = 0;

		// Write second line
		for (unsigned int i = 0; i < (maxStringSize * data.size()) + 1 + data.size(); ++i)
		{
			result += "-";
		}

		result += "\n";

		for (unsigned int i = 0; i < maxRows; ++i)
		{

			std::map<std::string, std::vector<std::string>>::iterator _it2;
			for (_it2 = data.begin(); _it2 != data.end(); _it2++)
			{
				result += "|";
				result += _it2->second.at(i);


				for (unsigned int j = 0; j < maxStringSize - _it2->second.at(i).size(); ++j)
				{
					result += " ";
				}
			}

			result += "|\n";
		}

		for (unsigned int i = 0; i < (maxStringSize * data.size()) + 1 + data.size(); ++i)
		{
			result += "-";
		}

		return result;
	}
};