// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 14, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_CUSTOMERORDER_H__
#define SDDS_CUSTOMERORDER_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utilities.h"
#include "Station.h"

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name{};
	std::string m_product{};
	unsigned int m_cntItem =0;
	Item** m_lstItem = nullptr;
	static size_t m_widthField;
public:
	CustomerOrder();
	~CustomerOrder();
	CustomerOrder(const std::string& src);
	CustomerOrder(const CustomerOrder&) {	throw "----> ERROR: Cannot make copies.";	}
	CustomerOrder& operator= (const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&) noexcept;
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};
#endif
