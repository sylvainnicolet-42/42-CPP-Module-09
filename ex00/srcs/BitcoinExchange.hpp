#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

class BitcoinExchange {
	public:
		BitcoinExchange(std::string database_filename); // constructor
		~BitcoinExchange(); // destructor

		void	showDatabase() const;
		void	getExchangeRateWithDate(const std::string& date) const;
	private:
		BitcoinExchange(); // default constructor
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);

		std::map<std::string, float> _database;
};

#endif