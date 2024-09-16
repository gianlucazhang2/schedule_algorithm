#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "compare.h"

Compare::Compare(std::vector<std::string> crn, std::vector<std::string> dept,
std::vector<std::string> code, std::vector<std::string> name, std::vector<std::string> day,
std::vector<std::string> s_time, std::vector<std::string> e_time, std::vector<std::string> room) {
	crns = crn; 
	depts = dept; 
	codes = code; 
	names = name; 
	days = day; 
	s_times = s_time;
	e_times = e_time; 
	rooms = room; 
}

void Compare::sortData(std::string type) {
	std::vector<std::vector<std::string>> array = {};
	for (int i = 0; i < crns.size(); i++) {
		std::vector<std::string> row = {};
		row.push_back(crns[i]);
		row.push_back(depts[i]);
		row.push_back(codes[i]);
		row.push_back(names[i]);
		row.push_back(days[i]);
		row.push_back(s_times[i]);
		row.push_back(e_times[i]);
		row.push_back(rooms[i]);
		array.push_back(row); 
	}
	
	if (type == "room") {
		std::sort(array.begin(), array.end(), compareDayTimeCode);
	}
	else {
		std::sort(array.begin(), array.end(), compareCodeDayTime);
	}
	 
	
	int index = 0; 
	for (int i = 0; i < array.size(); i++) {
		crns[index] = array[i][0];
		depts[index] = array[i][1];
		codes[index] = array[i][2];
		names[index] = array[i][3];
		days[index] = array[i][4];
		s_times[index] = array[i][5];
		e_times[index] = array[i][6];
		rooms[index] = array[i][7];	
		index++;
	}
}

//accessors
std::vector<std::string> Compare::getCRNS() {
	return crns; 
}

std::vector<std::string> Compare::getDepts() {
	return depts; 
}

std::vector<std::string> Compare::getCodes() {
	return codes; 
}

std::vector<std::string> Compare::getNames() {
	return names; 
}

std::vector<std::string> Compare::getDays() {
	return days; 
}

std::vector<std::string> Compare::getS_times() {
	return s_times; 
}

std::vector<std::string> Compare::getE_times() {
	return e_times; 
}

std::vector<std::string> Compare::getRooms() {
	return rooms; 
}

//turns weekday to int 
int dayToInt(std::string& day) {
	if (day == "Monday") return 1; 
	if (day == "Tuesday") return 2;
	if (day == "Wednesday") return 3;
	if (day == "Thursday") return 4;
	if (day == "Friday") return 5;
	return 0; 
}

//turns time string into min past midnight
int timeToMin(std::string& time) {
	int h, m; 
	char ampm[3]; 
	sscanf(time.c_str(), "%d:%d %s", &h, &m, ampm);
	if (strcmp(ampm, "AM") == 0) {
		if (h == 12) h = 0; 
	}
	else if (strcmp(ampm, "PM") == 0) {
		if (h != 12) h += 12; 
	}
	return (h*60) + m; 
}


//sorts entries by day, then time, then code
bool compareDayTimeCode(std::vector<std::string> a, std::vector<std::string> b) {
	int day1 = dayToInt(a[4]);
	int day2 = dayToInt(b[4]);
	int min1 = timeToMin(a[5]); 
	int min2 = timeToMin(b[5]);
	std::string code1 = a[2]; 
	std::string code2 = b[2]; 
	if (day1 != day2) {
		return day1 < day2; 
	}
	else if (min1 != min2) {
		return min1 < min2; 
	}
	else {
		return code1 < code2; 
	}
}

//sorts entries by day, then time, then code
bool compareCodeDayTime(std::vector<std::string> a, std::vector<std::string> b) {
	int day1 = dayToInt(a[4]);
	int day2 = dayToInt(b[4]);
	int min1 = timeToMin(a[5]); 
	int min2 = timeToMin(b[5]);
	std::string code1 = a[2]; 
	std::string code2 = b[2]; 
	if (code1 != code2) {
		return code1 < code2; 
	}
	else if (day1 != day2) {
		return day1 < day2; 
	}
	else {
		return min1 > min2; 
	}
}

//sorts by weekday (creative)
bool compareDays (std::string a, std::string b) {
	int day1 = dayToInt(a); 
	int day2 = dayToInt(b); 
	return day1 < day2;
}