class Compare {
public: 
	//constructor
	Compare(std::vector<std::string> crn, std::vector<std::string> dept,
std::vector<std::string> code, std::vector<std::string> name, std::vector<std::string> day,
std::vector<std::string> s_time, std::vector<std::string> e_time, std::vector<std::string> room); 
	
	//sorts the data
	void sortData(std::string type);
	
	//accessors
	std::vector<std::string> getCRNS();
	std::vector<std::string> getDepts();
	std::vector<std::string> getCodes(); 
 	std::vector<std::string> getNames();
	std::vector<std::string> getDays();
	std::vector<std::string> getS_times();
	std::vector<std::string> getE_times();
	std::vector<std::string> getRooms(); 
	
private: 
	std::vector<std::string> crns;
	std::vector<std::string> depts;
	std::vector<std::string> codes;
	std::vector<std::string> names;
	std::vector<std::string> days; 
	std::vector<std::string> s_times;
	std::vector<std::string> e_times;
	std::vector<std::string> rooms;
};

//turns weekday to int and sorts from least to greatest
int dayToInt(std::string& day);

//turns time string into minutes past midnight
//sorts from least to greatest
int timeToMin(std::string& time); 
bool compareDayTimeCode(std::vector<std::string> a, std::vector<std::string> b); 
bool compareCodeDayTime(std::vector<std::string> a, std::vector<std::string> b);
bool compareDays(std::string a, std::string b); 