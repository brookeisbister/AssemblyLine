// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 19, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H__
#define SDDS_LINEMANAGER_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#include "Workstation.h"
#include "CustomerOrder.h"

class LineManager {
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

	Workstation* m_firstStation = nullptr;
public:
	LineManager(const std::string filename, std::vector<Workstation*>& addresses, std::vector<CustomerOrder>& custOrders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif