#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// This class contains some generic, useful functions that might be used occaisonally.
// Author: Vincent Loignon

class Utils
{
public:

#pragma region Templates
	/*   Purpose:  This will convert all char values in the string to lower case and return it
	 *       Pre:  std::string input
	 *      Post:  std::string
	 ****************************************************************/
	static std::string toLowerString(std::string input)
	{
		std::string output = "";
		char c;

		for (size_t i = 0; i < input.size(); i++)
		{
			c = tolower(input[i]);
			output += c;
		}

		return output;
	}

	/*   Purpose:  This will generate a random binomial of type T
	 *       Pre:  None
	 *      Post:  T
	 ****************************************************************/
	template <class T>
	static T generateRandomBinomial()
	{
		return generateRandomNumber<T>() - generateRandomNumber<T>();
	}
	
	/*   Purpose:  This will generate a random number of type T
	 *       Pre:  None
	 *      Post:  T
	 ****************************************************************/
	template <class T>
	static T generateRandomNumber()
	{
		T r = (T)rand() / (T)RAND_MAX;
		return r;
	}

	/*   Purpose:  This will generate a number of type T between the min and max provided
	 *       Pre:  T min, T max
	 *      Post:  T
	 ****************************************************************/
	template <class T>
	static T generateNumber(T min, T max)
	{
		return (T)(min + (rand() % (int)max));
	}

	/*   Purpose:  This will clamp the value x of type T to the min and max provided
	 *       Pre:  T x, T min, T max
	 *      Post:  T
	 ****************************************************************/
	template <class T>
	static T clamp(T x, T min, T max)
	{
		return x < min ? min : (x > max ? max : x);
	}

	/*   Purpose:  This will convert the value of type T to a string and return it
	 *       Pre:  T value
	 *      Post:  std::string
	 ****************************************************************/
	template<class T>
	static std::string convertToString(T value)
	{
		std::stringstream ss;
		ss << value;

		return ss.str();
	}

	/*   Purpose:  This will convert the value of type T to an int and return it
	 *       Pre:  T value
	 *      Post:  int
	 ****************************************************************/
	template<class T>
	static int convertToInt(T value)
	{
		int theInt = 0;

		std::stringstream ss;
		ss << value;
		ss >> theInt;

		return theInt;
	}

	/*   Purpose:  This will return a bool which states whether or not object contains str
	 *       Pre:  std::string object, std::string str
	 *      Post:  bool
	 ****************************************************************/
	static bool stringContains(std::string object, std::string str)
	{
		bool result = false;

		if (object.size() < str.size() ||
		   (object.size() == str.size() && object != str))
			return false;

		int size = str.size();

		for (unsigned int i = 0; i < object.size(); i++)
		{
			if (i + size > object.size())
			{
				result = false;
				break;
			}

			result = true;

			for (int j = 0; j < size; j++)
			{
				if (object[i + j] != str[j])
				{
					result = false;
					break;
				}
			}

			if (result)
				break;
		}

		return result;
	}

	/*   Purpose:  This will check the input string for valid characters using a string provided. If it finds
	 *             any characters which are not valid, it will return false, otherwise it will return true
	 *       Pre:  std::string, std::string
	 *      Post:  bool
	 ****************************************************************/
	static bool stringContainsOnly(std::string input, std::string validChars)
	{
		bool isValid = false;

		// This will check each character in the input string with the validChars string. If a character in
		// the input string is not in the validChars string, it returns a false. Otherwise, it returns true.
		if (validChars.length() > 0)
		{
			for (size_t i = 0; i < input.length(); i++)
			{
				for (size_t j = 0; j < validChars.length(); j++)
				{
					if (input[i] == validChars[j])
					{
						isValid = true;
					}
				}

				if (isValid)
					isValid = false;
				else
					return false;
			}
		}
		else
			return false;

		return true;
	}

	/*   Purpose:  This will map the value of type T from its original "scope" to its new provided "scope" and return it
	 *       Pre:  T value, T istart, T istop, T ostart, T ostop
	 *      Post:  T
	 ****************************************************************/
	template<class T>
	static T map(T value, T istart, T istop, T ostart, T ostop)
	{
		return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
	}

	/*   Purpose:  This will calculate the distance between two points of type T and return it
	 *       Pre:  T startX, T startY, T endX, T endY
	 *      Post:  T
	 ****************************************************************/
	template<class T>
	static T distance(T startX, T startY, T endX, T endY)
	{
		return (T)sqrt(((endX - startX) * (endX - startX)) + ((endY - startY) * (endY - startY)));
	}

#pragma endregion

};

#endif