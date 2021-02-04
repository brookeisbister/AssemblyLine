// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 14, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {}
CustomerOrder::~CustomerOrder() {
	for (auto i = 0u; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
}
CustomerOrder::CustomerOrder(const std::string& src) {
	Utilities m_util;
	size_t start = 0;
	bool go = false;
	if (src.empty()) {
		m_name = {};
		m_product = {};
		m_cntItem = 0;
		m_lstItem = nullptr;
	}
	else {
		m_name = m_util.extractToken(src, start, go);
		if (go) {
			m_product = m_util.extractToken(src, start, go);
		}
		std::string strItems = src.substr(start, src.length() - start);
		m_cntItem = (std::count(strItems.begin(), strItems.end(), m_util.getDelimiter()))+1;
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0u; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(m_util.extractToken(src, start, go));
		}
		if (m_widthField < m_util.getFieldWidth())
			m_widthField = m_util.getFieldWidth();
	}
}
CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
	*this = std::move(other);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
	if (this != &other) {
		//transfer over
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		this->m_name = other.m_name;
		this->m_product = other.m_product;
		this->m_cntItem = other.m_cntItem;
		this->m_lstItem = other.m_lstItem;
		//reset other
		other.m_lstItem = nullptr;
		other.m_cntItem = 0;
	}
	return *this;
}
bool CustomerOrder::isOrderFilled() const {
	bool flag = true;
	for (unsigned int i = 0u; i < m_cntItem && flag; i++) {
		flag = m_lstItem[i]->m_isFilled;
	}

	return flag;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	for (unsigned int i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) {
			return m_lstItem[i]->m_isFilled;
		}
	}
	return true;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (unsigned int i = 0u; i < m_cntItem; i++) {
		if (station.getItemName().compare(m_lstItem[i]->m_itemName)==0) {
			if (station.getQuantity() >= 1) {
				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
			}
			else {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
			}
		}
	}
}
void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (unsigned int i = 0u; i < m_cntItem; i++) {
		os << "[";
		os << std::setw(6) << std::setfill('0') <<std::right<< m_lstItem[i]->m_serialNumber << "] ";
		os << std::setw(m_widthField) << std::setfill(' ') <<std::left<< m_lstItem[i]->m_itemName << " - ";
		os << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
}