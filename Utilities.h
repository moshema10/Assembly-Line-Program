// Name: Shehtab Masud
// Seneca Student ID: 119038206
// Seneca email: smasud3@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#include <iostream>
#include <string>

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds
{
	class Utilities
	{
		//specifies the length of the token extracted; used for display purposes; default value is 1.
		size_t m_widthField = 1;
		//separates the tokens in any given std::string object ex: , " "
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;

		//extracts a token from string str referred to by the first parameter
		//str represents a single line that has been read from an input file
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

	};
}



#endif // !SDDS_UTILITIES_H

