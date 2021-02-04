// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 19, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H__
#define SDDS_WORKSTATION_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include "CustomerOrder.h"
#include "Station.h"

class Workstation : public Station {
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(const std::string& src);
	Workstation(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation& operator=(Workstation&&) = delete;
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Workstation& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&)const;
	Workstation& operator+=(CustomerOrder&&);
};

#endif