#pragma once

#include <string>

struct Relation
{
	std::string attributes; // Use single letters to represent attributes for simplicity

	Relation(std::string att = "")
	{
		attributes = att;
	}

	void operator+=(std::string att)
	{
		bool exists = false;
		for (unsigned int i = 0; i < att.size(); i++)
		{
			for (unsigned int j = 0; j < attributes.size(); j++)
			{
				if (att[i] == attributes[j])
				{
					exists = true;
					break;
				}
			}

			if (!exists)
			{
				attributes += att[i];
			}
		}
	}
};