// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 19, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include "LineManager.h"

LineManager::LineManager(const std::string filename, std::vector<Workstation*>& addresses, std::vector<CustomerOrder>& custOrders) {
	//open the file
	std::ifstream file(filename);
	if (!file)
		throw std::string("Unable to open [") + filename + "] file.";
	//linking each Workstation object together to form the assembly line
	std::string record;
	Utilities m_util;
	while (!file.eof())
	{
		std::getline(file, record);
		if (!record.empty()) {
			size_t start = 0;
			bool go = false;
			std::string station1 = m_util.extractToken(record, start, go);
			if (go) {
				std::string station2 = m_util.extractToken(record, start, go);
				auto findStn = [&](Workstation* src)->bool { return   station1.compare(src->getItemName())==0;  };
				auto findNxt = [&](Workstation* src)->bool { return station2.compare(src->getItemName()) == 0;  };
				std::vector<Workstation*>::iterator it1 = std::find_if(addresses.begin(), addresses.end(), findStn);
				std::vector<Workstation*>::iterator it2 = std::find_if(addresses.begin(), addresses.end(), findNxt);
				(*it1)->setNextStation(*(*it2));
			}
		}
	}
	file.close();
	//Move all the CustomerOrder objects onto the back of the ToBeFilled queue
	for (size_t i = 0u; i < custOrders.size(); i++) {
		ToBeFilled.push_back(std::move(custOrders[i]));
	}
	//Copy all the Workstation objects into the AssemblyLine container
	AssemblyLine = addresses;
	//store the number of orders to be filled
	m_cntCustomerOrder = ToBeFilled.size();
	//find the first Workstation
	bool flag = true;
	int i = 0;
	while (flag) {
		m_firstStation = AssemblyLine[i];
		flag = std::any_of(AssemblyLine.begin(), AssemblyLine.end(), [&](const Workstation* src) {return src->getNextStation() == m_firstStation; });
		i++;
	};
}
bool LineManager::run(std::ostream& os) {
	//print iteration number
	static size_t count = 0;
	os << "Line Manager Iteration: " << ++count << std::endl;

	//check if empty
	if (!ToBeFilled.empty()) {
		*m_firstStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
		//run one cycle of the station's process move the CustomerOrder objects down the line.
	for(size_t x=0u; x < AssemblyLine.size();x++)
				AssemblyLine[x]->runProcess(os);
	//Loop through all stations on the assembly line and move the CustomerOrder objects down the line
	for (size_t x = 0u; x < AssemblyLine.size(); ++x) {
		AssemblyLine[x]->moveOrder();
		CustomerOrder order;
		if (AssemblyLine[x]->getIfCompleted(order)) {
			Completed.push_back(std::move(order));
		}
	}
	return Completed.size() == m_cntCustomerOrder;
}
void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (size_t i = 0u; i < Completed.size(); i++) {
		Completed[i].display(os);
	}
}
void LineManager::displayStations() const {
	for (size_t i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->display(std::cout);
	}
}
void LineManager::displayStationsSorted() const {
	const Workstation* stn = m_firstStation;
	while (stn != nullptr) {
		stn->display(std::cout);
		stn = stn->getNextStation();
	}

}