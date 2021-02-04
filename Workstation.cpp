// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 19, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Workstation.h"

Workstation::Workstation(const std::string& src):Station(src) {
	m_pNextStation = nullptr;
}
void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
		//m_orders.front().display(os);
	}
}
bool Workstation::moveOrder() {
	if (m_orders.empty()) {
		return false;
	}

		if (m_orders.front().isItemFilled(this->getItemName())&& m_pNextStation) {
			*m_pNextStation += std::move(m_orders.front());
			m_orders.pop_front();
			return true;
		}
	return false;
}
void Workstation::setNextStation(Workstation& station) {
	m_pNextStation = &station;
}
const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
}
bool Workstation::getIfCompleted(CustomerOrder& order) {
	if (m_orders.empty() == false && m_orders.front().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();
		return true;
}
	return false;
}
void Workstation::display(std::ostream& os) const{
	if (m_pNextStation != nullptr) {
		os << this->getItemName() << " --> " << m_pNextStation->getItemName()<<"\n";
	}
	else {
		os << this->getItemName() << " --> END OF LINE\n";
	}
}
Workstation& Workstation::operator+=(CustomerOrder&& src) {
	m_orders.push_back(std::move(src));
	return *this;
}