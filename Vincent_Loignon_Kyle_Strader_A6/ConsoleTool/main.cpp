#include "main.h"

int main()
{
	while (true)
	{
		printf("--------------------------------------------------------------------------------\n");
		printf("||               Welcome to Kyle & Vince's DBMS Console Tool!                 ||\n");
		printf("--------------------------------------------------------------------------------\n");

		int option = 0;

		while (true)
		{
			printf("What would you like?\n");
			printf("1. 3NF\n");
			printf("2. Exit\n");
			printf("> ");

			std::string temp = "";
			getline(std::cin, temp);

			option = Utils::convertToInt<std::string>(temp);
			
			if (option != 1 && option != 2)
			{
				printf("\nInvalid Input.\n\n");
				continue;;
			}

			break;
		}

		if (option == 1)
		{
			perform3NF();
		}
		else if (option == 2)
		{
			break;
		}

		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}

#pragma region ThirdNF Functions

void perform3NF()
{
	ThirdNF thirdNF;
	Relation origRel;
	std::vector<Relation> newRels;
	std::vector<FD> fds;
	int outputOption = 0;
	std::string outputFile = "";
	std::string results = "";

	// Get relation
	getRelation(origRel);

	// Get FDs
	getFDs(fds);

	// Get output file
	getOutput(outputOption, outputFile);

	thirdNF.normalize(origRel, fds);
	results = thirdNF.getResults();

	switch (outputOption)
	{
		case 1: // Console
			std::cout << results << std::endl;
			break;
		case 2: // File
			outputToFile(outputFile, results);
			break;
		case 3: // Console & File
			std::cout << results << std::endl;
			outputToFile(outputFile, results);
			break;
	}
}

void getRelation(Relation& out)
{
	while (true)
	{
		printf("\nEnter your Relation. White space will be ignored.\n");
		printf("Usage: R(A, B, ...) \n\n");
		printf("> ");

		// Grab their input
		std::string temp = "";
		getline(std::cin, temp);

		// extract the relation
		if (!extractRelation(temp, out))
		{
			printf("\nInvalid Usage.\n\n");
			continue;
		}

		break;
	}
}

void getFDs(std::vector<FD>& out)
{
	while (true)
	{
		printf("\nEnter your Functional Dependencies. White space will be ignored.\n");
		printf("Usage: B->C, AD->E, ...\n");
		printf("> ");

		std::string temp = "";
		getline(std::cin, temp);

		if (!extractFDs(temp, out))
		{
			out.clear();

			printf("\nInvalid Usage.\n\n");
			continue;;
		}

		break;
	}
}

void getOutput(int& option, std::string& file)
{
	while (true)
	{
		printf("\nWhere would you like it to output? (You can specify the file)\n");
		printf("Usage: \tconsole\n\tfile.txt\n\tboth file.txt\n");
		printf("> ");

		std::string temp = "";
		getline(std::cin, temp);

		// Just console
		if (temp == "console")
			option = 1;
		else
		{
			size_t i = temp.find("both ");

			// Just file
			if (i == std::string::npos)
			{
				option = 2;
				file = temp;
			}
			else // File and console
			{
				option = 3;

				file = temp.substr(5);
			}
		}

		break;
	}
}

#pragma endregion

#pragma region Input Functions

bool extractRelation(std::string input, Relation& out)
{
	// Remove spaces to make it easier to parse
	input = removeSpaces(input);

	// Find the first (, everyting before this is the relation's name
	size_t startIndex = input.find_first_of('(');
	size_t finalIndex = input.find_first_of(')');

	// If npos was returned, their format is wrong!
	if (startIndex == std::string::npos || finalIndex == std::string::npos)
		return false;

	std::string relName = "";
	std::string attributes = "";
	size_t i = 0;

	relName = input.substr(0, startIndex);
	attributes = input.substr(startIndex + 1, finalIndex - 2);

	if (relName == "")
		return false;

	// Split the attributes into individual attributes which we will then store in the relation
	while (true)
	{
		i = attributes.find_first_of(',');

		if (i == std::string::npos)
		{
			out += attributes;
			break;
		}

		out += attributes.substr(0, i);

		attributes = attributes.substr(i + 1);
	}

	return true;
}

bool extractFDs(std::string input, std::vector<FD>& out)
{
	// Remove spaces to make it easier to parse
	input = removeSpaces(input);

	std::string fd = "";
	std::string left = "";
	std::string right = "";
	size_t i = 0;

	// Split the attributes into individual attributes which we will then store in the relation
	while (true)
	{
		i = input.find_first_of(',');

		if (i == std::string::npos)
		{
			if (!extractFD(input, left, right))
				return false;

			out.push_back(FD(left, right));
			break;
		}

		fd = input.substr(0, i);

		if (!extractFD(fd, left, right))
			return false;

		out.push_back(FD(left, right));

		input = input.substr(i + 1);
	}

	return true;
}

bool extractFD(std::string fd, std::string& left, std::string& right)
{
	size_t i = fd.find("->");

	if (i == std::string::npos)
		return false;

	left = fd.substr(0, i);
	right = fd.substr(i + 2);

	return true;
}

std::string removeSpaces(std::string input)
{
	std::string output = "";

	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
			continue;

		output += input[i];
	}

	return output;
}

#pragma endregion

#pragma region Misc Functions

void outputToFile(std::string file, std::string val)
{
	std::ofstream out;

	out.open(file, std::ofstream::out);

	if (out.fail())
	{
		printf("\nThere was an error opening your file.\n");
		return;
	}

	out << val;

	out.close();
}

#pragma endregion