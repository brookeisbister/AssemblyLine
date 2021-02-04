// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 14, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Station.h"

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string& src){
	Utilities m_util;
	size_t start = 0;
	bool go = false;
	m_id = ++id_generator;
	if (src.empty()) {
		m_name = "";
		m_serial = 0;
		m_stock = 0;
		m_desc = "";
	}
	else {
	m_name = m_util.extractToken(src, start, go);
	if (go) {
		m_serial = stoi(m_util.extractToken(src, start, go));
	}
	if (go) {
	m_stock = stoi(m_util.extractToken(src, start, go));
	}
	if (m_widthField < m_util.getFieldWidth())
		m_widthField = m_util.getFieldWidth();
	m_desc =  m_util.extractToken(src, start, go);
	}
}

const std::string& Station::getItemName() const { return m_name; }

unsigned int Station::getNextSerialNumber() {
	//returns the next serial number to be used on the assembly line and increments m_serialNumber
	return m_serial++;
}

unsigned int Station::getQuantity() const { return m_stock; }

void Station::updateQuantity() { m_stock--; }

void Station::display(std::ostream& os, bool full) const{
	if (!full) {
		os << "[";
		os.width(3);
		os.fill('0');
		os << std::right << m_id << "] Item: ";
		os.width(m_widthField);
		os.fill(' ');
		os << std::left << getItemName() << " [";
		os.width(6);
		os.fill('0');
		os << std::right << m_serial << "]";
	}
	else {
		os << "[";
		os.width(3);
		os.fill('0');
		os << std::right << m_id << "] Item: ";
		os.width(m_widthField);
		os.fill(' ');
		os << std::left << getItemName() << " [";
		os.width(6);
		os.fill('0');
		os << std::right << m_serial;
		os << "] Quantity: ";
		os.width(m_widthField);
		os.fill(' ');
		os << std::left << getQuantity() << " Description: " << m_desc;
	}
	os << std::endl;
}
