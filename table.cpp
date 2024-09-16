#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "table.h"
#include "compare.h"

Table::Table(std::string inp, std::string out) {
	input = inp;
	output = out; 
	crns = {};
	depts = {};
	codes = {};
	names = {};
	days = {};
	s_times = {};
	e_times = {};
	rooms = {};
}

std::vector<std::string> Table::getRooms() {
	return rooms; 
}

std::vector<std::string> Table::getDays() {
	return days; 
}

//checks if the input file is empty
bool Table::isEmpty() {
	std::ifstream inp(input); 
    return inp.peek() == std::ifstream::traits_type::eof();
}

//finds the longest entry in vector (help with column width)
int Table::maxWidth(std::vector<std::string> courses) {
	int width = courses[0].length(); 
	for (std::string entry: courses) {
		if (entry.length() > width) {
			width = entry.length();
		}
	}
	return width; 
}

//creates dashes string for the table header for each column
std::string Table::dashes(int width) {
	std::string dash = "";
	for (int i = 0; i < width; i++) {
		dash += "-";
	}
	return dash; 
}

//calculates total rows needed
int Table::rowCount(std::vector<std::string> vect) {
	int count = 0; 
	for (std::string entry: vect) {
		count += entry.length(); 
	}
	return count; 
}

void Table::resetFile() {
	std::ofstream ofs;
	ofs.open(output, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void Table::printEntries(int count) {
	std::fstream ostr;
	ostr.open(output, std::fstream::app);
	ostr << count << " entries" << "\n\n"; 
	ostr.close(); 
}

std::vector<std::string> Table::convertDays() {
	std::vector<std::string> converted = {}; 
	for (std::string d: days) {
		if (d == "M") {converted.push_back("Monday");}
		if (d == "T") {converted.push_back("Tuesday");}
		if (d == "W") {converted.push_back("Wednesday");}
		if (d == "R") {converted.push_back("Thursday");}
		if (d == "F") {converted.push_back("Friday");}
	}
	return converted; 
}

//read input file and place each entry into each column
void Table::writeTable() {
	std::ifstream istr(input); 
	std::string line; 
	while (std::getline(istr, line)) {
		 // Split the line into individual entries
		std::istringstream iss(line);
		std::string entry;
		while (iss >> entry) {
			// Add each entry to the corresponding vector
			crns.push_back(entry);
			iss >> entry;
			depts.push_back(entry);
			iss >> entry;
			codes.push_back(entry);
			iss >> entry;
			names.push_back(entry);
			iss >> entry;
			days.push_back(entry);
			iss >> entry;
			s_times.push_back(entry);
			iss >> entry;
			e_times.push_back(entry);
			iss >> entry;
			rooms.push_back(entry);
		}
		//Creates new entry for classes with multiple meeting days
		if (days[days.size()-1].length() > 1) {  
			crns.push_back(crns[crns.size()-1]);
			depts.push_back(depts[depts.size()-1]); 
			codes.push_back(codes[codes.size()-1]); 
			names.push_back(names[names.size()-1]); 
			s_times.push_back(s_times[s_times.size()-1]); 
			e_times.push_back(e_times[e_times.size()-1]); 
			rooms.push_back(rooms[rooms.size()-1]); 
			std::string day = ""; 
			day += days[days.size()-1].at(1);
			days[days.size()-1]	= days[days.size()-1].substr(0,1); 		
			days.push_back(day); 
			
		}
	}
	days = convertDays(); 
}

void Table::printEmpty() {
	std::ofstream ostr(output);
	ostr << "No data available."; 
	ostr.close(); 
}

void Table::printHeader(std::string type, std::string spec, bool over) {
	//prints out the table header
	if (!over) {
		resetFile(); 
	} 
	std::fstream ostr;
	ostr.open(output, std::fstream::app);
	std::string dept_head = "";
	if (type == "room") {
		ostr << "Room " << spec << "\n"; 
		ostr << std::left << std::setw(6) << std::setfill(' ') << "Dept"; 
		dept_head = dashes(4) + "  "; 
	}
	else if (type == "custom") {
		ostr << spec << " Classes" << "\n"; 
	}
	else {
		ostr << "Dept " << spec << "\n"; 
	}
	
	//sets a vector to determine the width for each column
	//stores all the names and days of each class
	std::vector<std::string> dayLengths = {}; 
	std::vector<std::string> nameLengths= {}; 
	for (int i = 0; i < crns.size(); i++) {
		if (type == "room") {
			if (rooms[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]); 
			}
			else { continue;}
		}
		else if (type == "custom") {
			if (days[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]);
			}
		}
		else {
			if (depts[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]);
			}
			else {continue;}
		}
	}
	
	ostr << std::left << std::setw(11) <<  std::setfill(' ') << "Coursenum";
	if (maxWidth(nameLengths) < 11) {
		ostr << std::left << std::setw(13) <<  std::setfill(' ') << "Class Title";
	}
	else {
		ostr << std::left << std::setw(maxWidth(nameLengths)+2) <<  std::setfill(' ') << "Class Title";
	}
	ostr << std::left << std::setw(maxWidth(dayLengths)+2) <<  std::setfill(' ') << "Day";
	ostr << std::left << std::setw(12) <<  std::setfill(' ') << "Start Time";
	ostr << std::left << std::setw(8) <<  std::setfill(' ') << "End Time" << "\n";

	//prints out the dashes 
	if (maxWidth(nameLengths) < 11) {
		ostr << dept_head << dashes(9) << "  " << dashes(11) << "  " << dashes(maxWidth(dayLengths)) << "  " << dashes(10) << "  " << dashes(8) << "\n";
	}
	else {
		ostr << dept_head << dashes(9) << "  " << dashes(maxWidth(nameLengths)) << "  " << dashes(maxWidth(dayLengths)) << "  " << dashes(10) << "  " << dashes(8) << "\n";
	}
	 
	ostr.close(); 
}	

void Table::printData(std::string type, std::string spec) {
	//prints out the course data
	std::fstream ostr;
	ostr.open(output, std::fstream::app);
	//tests to see if the specified room exists
    bool exist = false; 
	int count = 0; 
	
	//sorts the data
	Compare sort(crns, depts, codes, names, days, s_times, e_times, rooms); 
	sort.sortData(type); 
	crns = sort.getCRNS(); 
	depts = sort.getDepts(); 
	codes = sort.getCodes(); 
	names = sort.getNames();
	days = sort.getDays(); 
	s_times = sort.getS_times();
	e_times = sort.getE_times();
	rooms = sort.getRooms(); 
	
	//sets a vector to determine the width for each column
	//stores all the names and days of each class
	std::vector<std::string> dayLengths = {}; 
	std::vector<std::string> nameLengths= {}; 
	for (int i = 0; i < crns.size(); i++) {
		if (type == "room") {
			if (rooms[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]); 
			}
			else { continue;}
		}
		else if (type == "custom") {
			if (days[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]);
			}
		}
		else {
			if (depts[i] == spec) {
				dayLengths.push_back(days[i]); 
				nameLengths.push_back(names[i]);
			}
			else {continue;}
		}
	}
				
	for (int i = 0; i < crns.size(); i++) {
		if (type == "room") {
			if (rooms[i] == spec) {
				exist = true;
				count++; 				
				ostr << std::left << std::setw(6) << std::setfill(' ') << depts[i];
				ostr << std::left << std::setw(11) << std::setfill(' ') << codes[i];
				if (maxWidth(nameLengths) < 11) {
					ostr << std::left << std::setw(13) <<  std::setfill(' ') << names[i];
					}
				else {
					ostr << std::left << std::setw(maxWidth(nameLengths)+2) <<  std::setfill(' ') << names[i];
				}				
				ostr << std::left << std::setw(maxWidth(dayLengths)+2) <<  std::setfill(' ') << days[i];
				ostr << std::left << std::setw(12) <<  std::setfill(' ') << s_times[i];
				ostr << std::left << std::setw(8) <<  std::setfill(' ') << e_times[i] << "\n";
			}
			else { continue; }			
		}
		else if (type == "custom") {
			if (days[i] == spec) {
				exist = true;
				count++; 
				ostr << std::left << std::setw(11) << std::setfill(' ') << codes[i]; 
				if (maxWidth(nameLengths) < 11) {
					ostr << std::left << std::setw(13) <<  std::setfill(' ') << names[i];
				}
				else {
				ostr << std::left << std::setw(maxWidth(nameLengths)+2) <<  std::setfill(' ') << names[i];
			}
				ostr << std::left << std::setw(maxWidth(dayLengths)+2) <<  std::setfill(' ') << days[i];
				ostr << std::left << std::setw(12) <<  std::setfill(' ') << s_times[i];
				ostr << std::left << std::setw(8) <<  std::setfill(' ') << e_times[i] << "\n";
			}
		}
		else {
			if (depts[i] == spec) {
				exist = true; 
				count++; 
				ostr << std::left << std::setw(11) << std::setfill(' ') << codes[i]; 
				if (maxWidth(nameLengths) < 11) {
					ostr << std::left << std::setw(13) <<  std::setfill(' ') << names[i];
				}
				else {
					ostr << std::left << std::setw(maxWidth(nameLengths)+2) <<  std::setfill(' ') << names[i];
				}
				ostr << std::left << std::setw(maxWidth(dayLengths)+2) <<  std::setfill(' ') << days[i];
				ostr << std::left << std::setw(12) <<  std::setfill(' ') << s_times[i];
				ostr << std::left << std::setw(8) <<  std::setfill(' ') << e_times[i] << "\n";
			}
			else { continue; }
		}
		
	}
	 //prints empty if specified doesn't exist
	if (!exist) {
		resetFile(); 
		ostr << "No data available."; 
	}
	
	//print out number of entries 
	ostr.close();
	if (exist) {
		printEntries(count);
	}
}


