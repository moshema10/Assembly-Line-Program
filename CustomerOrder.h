

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"
namespace sdds
{


	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName{};
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name{}; //The name of the customer (e.g: John, Sara, etc)
		std::string m_product{}; //The name of the product being assembled (e.g: Desktop, Laptop, etc)
		size_t m_cntItem{}; //a count of the number of items in the customer's order
		Item** m_lstItem = nullptr; //a dynamically allocated array of pointers.Each element of the array points							to a dynamically allocated object of type Item.

		static size_t m_widthField;

	public:
		CustomerOrder() = default;

		CustomerOrder(const std::string& str);

		//Copy
		CustomerOrder(const CustomerOrder& other)
		{
			throw "Error";
		}
		CustomerOrder& operator=(const CustomerOrder& other) = delete;

		//Move
		CustomerOrder(CustomerOrder&& other) noexcept
		{
			*this = std::move(other);
		}
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		~CustomerOrder();

		//

		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;
	};
}


#endif // !SDDS_CUSTOMERORDER_H

