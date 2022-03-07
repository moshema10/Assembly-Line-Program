// Name: Shehtab Masud
// Seneca Student ID: 119038206
// Seneca email: smasud3@myseneca.ca
// Date of completion: 12/5/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include "Workstation.h"
namespace sdds
{
	//The LineManager class manages an assembly line of active stations 
	class LineManager
	{
		//All the Workstaions 1,2,3
		std::vector<Workstation*> activeLine{};
		//Total Number of CustomerOrder Objects
		size_t m_cntCustomerOrder{};
		//Points to the first active station in the current assemply line
		Workstation* m_firstStation{};

	public:

		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}


#endif // !SDDS_LINEMANAGER_H

