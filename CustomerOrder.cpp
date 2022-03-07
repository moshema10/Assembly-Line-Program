

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0u;
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities temp_utility{};
		size_t pos = 0u;
		bool more = false;

	
		m_name = temp_utility.extractToken(str, pos, more); //Cornel B.
		m_product = temp_utility.extractToken(str, pos, more); //1-Room Home Office
		//Bed|Dresser|Office Chair|Desk|Bookcase|Bookcase|Filing Cabinet

		m_cntItem = unsigned(std::count(str.begin()+pos, str.end(), temp_utility.getDelimiter())) + 1;
		//for (size_t i = pos; i < str.length(); i++)
		//{
		//	if (str[i] == temp_utility.getDelimiter())
		//	{
		//		m_cntItem++;
		//	}
		//}
		//m_cntItem++;
		
		//Allocate
		m_lstItem = new Item* [m_cntItem];


		for (size_t i = 0; i < m_cntItem; i++)
		{
			const std::string& oneItem = temp_utility.extractToken(str, pos, more);

			//Allocate
			m_lstItem[i] = new Item(oneItem);
		}

		if (m_widthField < temp_utility.getFieldWidth())
		{
			m_widthField = temp_utility.getFieldWidth();
		}

	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other)
		{
			//cleanup
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}

			this->m_name = other.m_name;
			this->m_product = other.m_product;
			this->m_lstItem = other.m_lstItem;
			this->m_cntItem = other.m_cntItem;

			other.m_name = {};
			other.m_product = {};
			other.m_lstItem = nullptr;
			other.m_cntItem = 0u;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete this->m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isFilled() const
	{
		bool check = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				check = false;
				break;
			}
		}
		return check;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const 
	{
		bool check = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (m_lstItem[i]->m_isFilled == false)
				{
					check = false;
					break;
				}
			}
		}
		return check;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() >= 1)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled ";
				}
				else
				{
					os << "    Unable to fill ";
				}
				os << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
			}
		}




	}

	void CustomerOrder::display(std::ostream& os) const
	{
		//CUSTOMER_NAME - PRODUCT
		//[SERIAL] ITEM_NAME - STATUS
		//[SERIAL] ITEM_NAME - STATUS
		int width = 6;
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << setw(width) << right << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setfill(' ') << left << setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << endl;
			}
			else
			{
				os << "TO BE FILLED" << endl;
			}
		}


	}


}
