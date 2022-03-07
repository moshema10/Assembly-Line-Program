


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds
{
	extern std::deque<CustomerOrder> pending; //To be placed at the first station.
	extern std::deque<CustomerOrder> completed;//Removed from the last station.
	extern std::deque<CustomerOrder> incomplete;//could not be filled completely.

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};

	public:
		Workstation() = default;
		Workstation(const std::string& str);

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		Workstation& operator+=(CustomerOrder&& newOrder);
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;

		//Copy and Move Deleted
		Workstation(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};
}



#endif // !SDDS_WORKSTATION_H
