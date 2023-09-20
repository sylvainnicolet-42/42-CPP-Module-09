#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string database_filename) {
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

void	BitcoinExchange::getExchangeRateWithDate(const std::string& date) const {
	std::cout << "=== Searching for exchange rate with date [" << date << "] ===" << std::endl;

	std::map<std::string, float>::const_iterator it = this->_database.find(date);
	if (it == this->_database.end()) {
		// Try to find the closest date and return that exchange rate
		std::map<std::string, float>::const_iterator it2 = this->_database.lower_bound(date);
		if (it2 != this->_database.begin()) {
			it2--;
			std::cout << "No date found" << std::endl;
			std::cout << "Closest exchange rate [" << it2->second << "]" << std::endl;
			return;
		}
		std::cout << "No date found" << std::endl;
		std::cout << "No closest exchange rate" << std::endl;
		return;
	}
	std::cout << "Exchange rate [" << it->second << "]" << std::endl;
	std::cout << std::endl;
}