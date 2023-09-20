#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

class BitcoinExchange {
	public:
		BitcoinExchange(const std::string& database_filename); // constructor
		~BitcoinExchange(); // destructor
		BitcoinExchange(BitcoinExchange const &src); // copy constructor
		BitcoinExchange &operator=(BitcoinExchange const &rhs); // assignment operator

		void	showDatabase() const;
		void	displayFromFile(const std::string& filename) const;
	private:
		BitcoinExchange(); // default constructor
		float	getExchangeRateWithDate(const std::string& date) const;

		std::map<std::string, float> _database;
};

#endif