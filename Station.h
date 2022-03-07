



#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>
namespace sdds
{
	class Station
	{
		int m_Station_id = 0;
		std::string m_Station_desc{};

		std::string m_item_name{};
		size_t m_item_Serialnum = 0u;
		size_t m_item_Instock = 0u;

		//For item name, serial number and quantity.
		static size_t m_widthField;

		//a variable used to generate IDs for new instances of type Station.Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented.
		static size_t m_id_generator;

	public:
		Station() = default;
		Station(const std::string& line);

		const std::string& getItemName() const;
		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}


#endif // !SDDS_STATION_H

