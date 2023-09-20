
#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	(void) argv;
	if (argc != 2) {
		std::cout << "Usage: ./btc [file]" << std::endl;
		return 1;
	}
	BitcoinExchange exchange("data_small.csv");
	exchange.showDatabase();
	exchange.getExchangeRateWithDate("2009-01-01");

	return 0;
}
