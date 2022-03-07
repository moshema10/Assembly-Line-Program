

#include <iostream>
#include <string>
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"


using namespace std;

namespace sdds
{
	deque<CustomerOrder> pending{};
	deque<CustomerOrder> completed{};
	deque<CustomerOrder> incomplete{};

	Workstation::Workstation(const std::string& line) : Station(line)
	{

	}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.empty())
		{
			return false;
		}

		CustomerOrder& currentOrder = m_orders.front();
		std::string item = this->getItemName();

		if (currentOrder.isItemFilled(item) || getQuantity() == 0) //IF true no more service IF true Out of stock. Item is filled
		{
			//moving to the next station
			if (m_pNextStation) //next station exists
			{
				*m_pNextStation += std::move(currentOrder);
				m_orders.pop_front(); //remove the first order from the queue.
				return true;
			}
			if (currentOrder.isFilled()) //nextStation doest exist and order is filled with its items
			{
				completed.push_back(std::move(currentOrder));
				m_orders.pop_front(); //remove the first order from the queue.
				return true;
			}
			else //Current Order is not filled and No Next Station
			{
				incomplete.push_back(std::move(currentOrder));
				m_orders.pop_front(); //remove the first order from the queue.
				return true;
			}
		}
		return false;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

	void Workstation::display(std::ostream& os) const
	{
		//ITEM_NAME-- > NEXT_ITEM_NAME

		//ITEM_NAME
		os << getItemName();
		if (m_pNextStation == nullptr)
		{
			os << " --> End of Line" << endl;
		}
		else
		{
			os << " --> " << m_pNextStation->getItemName() << endl;
		}
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}



}
