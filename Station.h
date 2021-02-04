// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 6, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_STATION_H__
#define SDDS_STATION_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utilities.h"

class Station {
	size_t m_id;
	std::string m_name;
	std::string m_desc;
	unsigned m_serial;
	unsigned int m_stock;

	static size_t m_widthField;
	static size_t id_generator;
public:
	Station(const std::string& src);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};
#endif