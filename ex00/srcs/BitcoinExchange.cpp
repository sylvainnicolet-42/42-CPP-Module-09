#include "BitcoinExchange.hpp"

// Prototypes
static bool isDateValid(const std::string& date);
static bool isValueValid(const std::string& value);

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& database_filename) {
	std::ifstream db_file(database_filename);
	if (!db_file.is_open()) {
		std::cout << "Error: could not open file " << database_filename << std::endl;
		return;
	}

	std::string line;
	std::getline(db_file, line); // skip first line
	while (std::getline(db_file, line)) {
		std::string key = line.substr(0, line.find(','));
		std::string value = line.substr(line.find(',') + 1);
		this->_database[key] = std::stof(value);
	}
	db_file.close();
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	if (this != &rhs) {
		this->_database = rhs._database;
	}
	return *this;
}

void BitcoinExchange::showDatabase() const {
	std::cout << "=== Database ===" << std::endl;
	std::map<std::string, float>::const_iterator it = this->_database.begin();
	while (it != this->_database.end()) {
		std::cout << "[" << it->first << "] => " << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}

float	BitcoinExchange::getExchangeRateWithDate(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = this->_database.find(date);
	if (it == this->_database.end()) {
		// Try to find the closest date and return that exchange rate
		std::map<std::string, float>::const_iterator it2 = this->_database.lower_bound(date);
		if (it2 != this->_database.begin()) {
			it2--;
			return it2->second;
		}
		return -1;
	}
	return it->second;
}

void	BitcoinExchange::displayFromFile(const std::string &filename) const {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Error: could not open file " << file << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // skip first line
	while (std::getline(file, line)) {

		// Check if there is a valid separator "|"
		if (line.find('|') == std::string::npos) {
			std::cout << "Error: separator '|' not found => " << line << std::endl;
			continue;
		}

		// Trim the line
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

		std::string date = line.substr(0, line.find('|'));
		std::string value = line.substr(line.find('|') + 1);

		// Check if the date is valid
		if (!isDateValid(date)) {
			std::cout << " => [" << date << "]" << std::endl;
			continue;
		}

		// Check if the value is valid
		if (!isValueValid(value)) {
			std::cout << " => [" << value << "]" << std::endl;
			continue;
		}

		// Display the result
		float exchange_rate = this->getExchangeRateWithDate(date);
		if (exchange_rate == -1) {
			std::cout << "Error: no exchange rate found for date [" << date << "]" << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << exchange_rate * std::stof(value) << std::endl;
	}
}

static bool isDateValid(const std::string& date) {
	if (date.length() != 10) {
		std::cout << "Error: date format is not YYYY-MM-DD";
		return false;
	}

	if (date[4] != '-' || date[7] != '-') {
		std::cout << "Error: date format is not YYYY-MM-DD";
		return false;
	}

	std::string year = date.substr(0, 4);
	if (year.find_first_not_of("0123456789") != std::string::npos) {
		std::cout << "Error: Year is not a number";
		return false;
	}

	std::string month = date.substr(5, 2);
	if (month.find_first_not_of("0123456789") != std::string::npos) {
		std::cout << "Error: Month is not a number";
		return false;
	}
	if (std::stoi(month) < 1 || std::stoi(month) > 12) {
		std::cout << "Error: Month must be between 1 and 12";
		return false;
	}

	std::string day = date.substr(8, 2);
	if (day.find_first_not_of("0123456789") != std::string::npos) {
		std::cout << "Error: Day is not a number";
		return false;
	}

	switch (std::stoi(month)) {
		case 1:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 2:
			if (std::stoi(day) < 1 || std::stoi(day) > 28) {
				std::cout << "Error: Day must be between 1 and 28";
				return false;
			}
			break;
		case 3:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 4:
			if (std::stoi(day) < 1 || std::stoi(day) > 30) {
				std::cout << "Error: Day must be between 1 and 30";
				return false;
			}
			break;
		case 5:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 6:
			if (std::stoi(day) < 1 || std::stoi(day) > 30) {
				std::cout << "Error: Day must be between 1 and 30";
				return false;
			}
			break;
		case 7:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 8:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 9:
			if (std::stoi(day) < 1 || std::stoi(day) > 30) {
				std::cout << "Error: Day must be between 1 and 30";
				return false;
			}
			break;
		case 10:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		case 11:
			if (std::stoi(day) < 1 || std::stoi(day) > 30) {
				std::cout << "Error: Day must be between 1 and 30";
				return false;
			}
			break;
		case 12:
			if (std::stoi(day) < 1 || std::stoi(day) > 31) {
				std::cout << "Error: Day must be between 1 and 31";
				return false;
			}
			break;
		default:
			std::cout << "Error: Month is not valid";
			return false;
	}

	return true;
}

static bool	isValueValid(const std::string& value) {
	if (value.length() == 0) {
		std::cout << "Error: Value is empty";
		return false;
	}

	if (value.find_first_not_of("0123456789.-") != std::string::npos) {
		std::cout << "Error: Value is not a number";
		return false;
	}

	if (std::count(value.begin(), value.end(), '.') > 1) {
		std::cout << "Error: Value must have only one '.'";
		return false;
	}

	if (std::count(value.begin(), value.end(), '-') > 1) {
		std::cout << "Error: Value must have only one '-'";
		return false;
	}

	if (value[0] == '.') {
		std::cout << "Error: '.' must not be the first character";
		return false;
	}

	if (value[value.length() - 1] == '.') {
		std::cout << "Error: '.' must not be the last character";
		return false;
	}

	if (std::count(value.begin(), value.end(), '-') == 1) {
		if (value[0] != '-') {
			std::cout << "Error: '-' must be the first character";
			return false;
		}
	}

	if (std::stod(value) < 0 || std::stod(value) > 1000) {
		std::cout << "Error: Value must be between 0 and 1000";
		return false;
	}

	return true;
}