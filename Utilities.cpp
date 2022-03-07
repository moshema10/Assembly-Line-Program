// Name: Shehtab Masud
// Seneca Student ID: 119038206
// Seneca email: smasud3@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <iostream>
#include <sstream>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds
{
	char Utilities::m_delimiter = ',';


	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	//"apple,orange,banana,kiwi,strawberry,yellow watermellon"
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token{};
		more = false;
		if (next_pos < str.length())
		{
			if (str[next_pos] == m_delimiter)
			{
				more = false;
				throw "Delimiter Found";
			}
			token = str.substr(next_pos, str.length()); //token = apple,......,yellow watermelon
			stringstream ss(token);
			if (getline(ss, token, m_delimiter)) //token = apple
			{
				if (token.length() > m_widthField)
				{
					m_widthField = token.length();
				}
				next_pos += (token.length() + 1);
				if (next_pos < str.length())
				{
					more = true;

				}
			}
		}
		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}