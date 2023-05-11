#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <map>
#include <iomanip>


class TooManyArgumetns : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error: too many arguments");
		}
};

class NotEnoughArgumetns : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error: not enough arguments");
		}
};

class FileNotOpen : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error: file not open");
		}
};

class ParseError : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error: parsing failed");
		}
};

//operator overloading < for struct tm

bool operator<(const std::tm &a, const std::tm &b) //orverloading < operator for struct tm or map will not work
{
	std::time_t	ta = std::mktime(const_cast<std::tm *>(&a)); //mktime() converts a tm structure to a time_t value
	std::time_t tb = std::mktime(const_cast<std::tm *>(&b)); //
	return (ta < tb);
}

void read_db(std::map<std::tm, double> &db)
{
	char c;

	std::tm 		tm = {};
	float			price;

	std::ifstream 	file; //ifstream stand for stand for input file stream
	std::string 	line;

	file.open("data.csv");
	if (!file.is_open()) //is_open() checks if the file is open
		throw FileNotOpen();
	getline(file, line); //getline() reads a line from the file


	while (getline(file, line))
	{
		std::istringstream ss(line); //istringstream is an input stream class to operate on strings

		// ss >> tm.tm_year >> c >> tm.tm_mon >> c >> tm.tm_mday >> c >> price;
		ss >> std::get_time(&tm, "%Y-%m-%d"); //get_time() parses the input stream according to the format string
		if (ss.fail())
			throw ParseError();

		//The extraction operator >> stops reading from the input string as soon as it encounters the delimiter , which separates the date string and the floating-point number.
		//get time stoped at the first , so we need to skip it
		ss >> c >> price;

		//display the time
		// std::cout << tm.tm_year << std::endl;
		// std::cout << tm.tm_mon << std::endl;
		// std::cout << price << std::endl;

		db.insert(std::pair<std::tm, double>(tm, price));;
	}
	file.close();
}

void display(std::map<std::tm, double> &db, char *file_name)
{
	char 	c;
	std::tm tm = {};
	double 	number;
	
	std::ifstream 	file; //ifstream stand for stand for input file stream
	std::string 	line;

	file.open(file_name);
	if (!file.is_open()) //is_open() checks if the file is open
		throw FileNotOpen();
	getline(file, line); //getline() reads a line from the file	

	//compare the date in the file with the date in the map
	while (getline(file, line))
	{
		std::istringstream ss(line); //istringstream is an input stream class to operate on strings
		ss >> std::get_time(&tm, "%Y-%m-%d"); //get_time() parses the input stream according to the format string
		if (ss.fail())
			std::cout << "Error: parsing failed" << std::endl;
		ss >> c >> number;

		//find the date in the map
		if (db.find(tm) == db.end())
			std::cout << "Error: date not found" << std::endl;
		else if (number < 0)
			std::cout << "Error: negative number or empty number" << std::endl;
		else if (number > 22000000)
			std::cout << "Error: SBF is proud of you, you are able to own more btc than exist" << std::endl;
		else
			std::cout << std::put_time(&tm, "%Y-%m-%d") << " => " << number << " = " << number * db[tm] << std::endl;
	}
}
		



int main(int _argc, char** _argv)
{
	(void)_argv;
	//create a map
	std::map<std::tm, double> db;

	try
	{
		if (_argc == 1)
			throw NotEnoughArgumetns();
		if	(_argc > 2)
			throw TooManyArgumetns();
		if (_argc == 2)
		{
			read_db(db);
			display(db, _argv[1]);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}