#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "table.h"
#include "compare.h"

int main(int argc, char *argv[]) {
	
	//arguments
	std::string input = argv[1];
	std::string output = argv[2]; 
	std::string type = argv[3];
	std::string spec = ""; 
	if (argc == 5) {
		spec = argv[4];
	}
	 
	Table dataTable(input, output); 
	dataTable.writeTable();
	
	//empty cases
	if (type == "dept" && argc == 4) {
		dataTable.printEmpty();
        exit(0); 		
	}
	if (dataTable.isEmpty()) {
		dataTable.printEmpty();
		exit(0);
	}
	 
	bool over = false; 
	
	if (type == "dept") { 
		dataTable.printHeader(type, spec, over);
		dataTable.printData(type, spec); 
	} 
	else if (type == "custom") {
		std::vector<std::string> dayList = {};
		std::vector<std::string> days = dataTable.getDays();
		std::vector<std::string> weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}; 
		for (std::string weekday: weekdays) {
			for (std::string day: days) {
				if (std::find(dayList.begin(), dayList.end(), day) == dayList.end()) {
					dayList.push_back(day); 
				}
			}
		}
		std::sort(dayList.begin(), dayList.end(), compareDays);  
		for (std::string day: dayList) {
			if (day == dayList[1]) {
				over = true; 
			}
			dataTable.printHeader(type, day, over); 
			dataTable.printData(type, day); 
		}
	}
	else {
		if (argc == 5) {
			dataTable.printHeader(type, spec, over); 
			dataTable.printData(type, spec); 
		}
		else {
			std::vector<std::string> roomsList = {};
			std::vector<std::string> rooms = dataTable.getRooms();
			for (std::string room: rooms) {
				if (std::find(roomsList.begin(), roomsList.end(), room) == roomsList.end()) {
					roomsList.push_back(room); 
				}
			}
			//sort roomsList alphabetically
			std::sort(roomsList.begin(), roomsList.end()); 
			
			for (std::string r: roomsList) {
				if (r == roomsList[1]) {
					over = true;
				}
				dataTable.printHeader(type, r, over); 
				dataTable.printData(type, r);  
			}
		}
	}

	
	
	return 0; 
}