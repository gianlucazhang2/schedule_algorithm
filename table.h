class Table {
public:
	//constructor; parameters for input and output files
	Table(std::string input, std::string output); 
	
	//accessor
	std::vector<std::string> getRooms();
	std::vector<std::string> getDays();	
	
	//checks if the input file is empty
	bool isEmpty(); 
	
	//finds the longest entry in vector (help with column width)
	int maxWidth(std::vector<std::string> courses);
	
	//creates dashes string for the table header for each column
	std::string dashes(int width);
	
	//calculates total rows needed
	int rowCount(std::vector<std::string> vect);
	
	//overwrites the output file
	void resetFile(); 
	
	//prints out no data available
	void printEmpty();
	
	//prints the number of entries for each table
	void printEntries(int count); 
	
	//converts M-F to Monday-Friday
	std::vector<std::string> convertDays();
	
	//read input file and place each entry into each column
	void writeTable();
	
	//prints out the table header
	void printHeader(std::string type, std::string spec, bool over);
	
	//prints out the course data
	void printData(std::string type, std::string spec);
private:
	std::string input;
	std::string output; 
	std::vector<std::string> crns;
	std::vector<std::string> depts;
	std::vector<std::string> codes;
	std::vector<std::string> names;
	std::vector<std::string> days;
	std::vector<std::string> s_times;
	std::vector<std::string> e_times;
	std::vector<std::string> rooms;
};
	
	