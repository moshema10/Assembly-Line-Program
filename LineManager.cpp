// Name: Shehtab Masud
// Seneca Student ID: 119038206
// Seneca email: smasud3@myseneca.ca
// Date of completion: 12/5/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>
#include <vector>
#include <iterator>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	//For counting run() fucntion
	static size_t count = 0;
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		// LineManager lm(argv[4], theStations); 
		//stations param is the collection of worksations available for the assembly line.

		std::ifstream File(file);
		if (!File)
		{
			throw string("Unable to open [") + file + "] file.";
		}

		//using Utilities module

		Utilities temp_utility{};
		std::string line{};
		std::string _Workstation{};

		while (!File.eof())
		{
			//WORKSTATION|NEXT_WORKSTATION.
			if (getline(File, line))
			{
				size_t pos = 0u;
				bool more = false;

				_Workstation = temp_utility.extractToken(line, pos, more);

				auto match = [&_Workstation](const Station* IS)
				{
					if (IS->getItemName() == _Workstation)
						return true;
					return false;
				};


				auto station = std::find_if(stations.begin(), stations.end(), match);
				activeLine.push_back(*station);

				if (more)
				{
					_Workstation = temp_utility.extractToken(line, pos, more);
					auto station = std::find_if(stations.begin(), stations.end(), match);
					activeLine.back()->setNextStation(*station);
				}

			}
		}
		File.close();
		
		//
		std::find_if(activeLine.begin(), activeLine.end(), [this](Workstation* oneStation) {
			const std::string& name = oneStation->getItemName();

			int occurance = count_if(activeLine.begin(), activeLine.end(), [name](Workstation* station) {
				return station->getItemName() == name;
				});

			if (occurance == 1)
			{
				m_firstStation = oneStation;
				return true;
			}
			else
			{
				return false;
			}
			});
		m_cntCustomerOrder = pending.size();
		
	}

	void LineManager::linkStations()
	{
		vector<Workstation*> temp{};
		temp.push_back(m_firstStation); //Bed
		temp.push_back(m_firstStation->getNextStation());// dresser
		size_t size = activeLine.size(); //8

		for (size_t i = 0u; i < size - 2; i++)
		{
			temp.push_back(temp.back()->getNextStation());
		}
		activeLine = temp;
	}

	bool LineManager::run(std::ostream& os)
	{
		count++;
		os << "Line Manager Iteration: " << count << endl;
		//if orders on pending add it
		if (!pending.empty())
		{
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		//Filling each station
		for (auto& station : activeLine)
		{
			station->fill(os);
		}
		//Moving a order down the line of WS
		for (auto& station : activeLine)
		{
			station->attemptToMoveOrder();
		}
		if ((completed.size() + incomplete.size()) == m_cntCustomerOrder)
		{
			return true;
		}
		return false;

	}

	void LineManager::display(std::ostream& os) const
	{
		for (auto& ws : activeLine)
			ws->display(os);
	}
}

