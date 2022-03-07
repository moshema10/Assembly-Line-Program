// Name: Shehtab Masud
// Seneca Student ID: 119038206
// Seneca email: smasud3@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"
#include "Station.h"

using namespace std;
namespace sdds
{
	size_t Station::m_widthField = 0u;
	size_t Station::m_id_generator = 0u;

	Station::Station(const std::string& line)
	{
		Utilities temp_utility{};
		size_t pos = 0u;
		bool more = false;

		m_id_generator++;
		m_Station_id = m_id_generator;
		m_item_name = temp_utility.extractToken(line, pos, more);
		m_item_Serialnum = std::stoul(temp_utility.extractToken(line, pos, more));
		m_item_Instock = std::stoul(temp_utility.extractToken(line, pos, more));
		if (Station::m_widthField < temp_utility.getFieldWidth())
		{
			m_widthField = temp_utility.getFieldWidth();
		}
		
		m_Station_desc = temp_utility.extractToken(line, pos, more);

	}

	const std::string& Station::getItemName() const
	{
		return m_item_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_item_Serialnum++;
	}

	size_t Station::getQuantity() const
	{
		return m_item_Instock;
	}

	void Station::updateQuantity()
	{
		if (m_item_Instock > 0)
			--m_item_Instock;
	}

	void Station::display(std::ostream& out, bool full) const
	{
		int width = 6;
		int width2 = 3;
		//[ID] Item NAME[SERIAL] Quantity: QTY Description : DESCRIPTION
		// 
		//[ID]
		out << "[" << setfill('0') << setw(width2) << right << m_Station_id << "] ";
		//Item NAME
		out << "Item: " << setfill(' ') << setw(m_widthField) << left << m_item_name;
		//[SERIAL]
		out << " [" << setfill('0') << setw(width) << right << m_item_Serialnum << "]";
		if (full)
		{

			//Quantity: QTY
			out << " Quantity: " << setfill(' ') << left << setw(m_widthField) << m_item_Instock;
			//Description
			out << " Description: " << m_Station_desc << endl;
		}
		else
		{
			out << endl;
		}
	}




}

