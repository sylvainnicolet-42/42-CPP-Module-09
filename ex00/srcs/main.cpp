
#include <iostream>
#include "BitcoinExchange.hpp"

void	test_copy_constructor() {
	std::cout << "=== Test copy constructor ===" << std::endl;
	BitcoinExchange exchange("data_small.csv");
	exchange.showDatabase();

	// Test the copy constructor
	const BitcoinExchange& exchange2(exchange);
	exchange2.showDatabase();
}

void	test_assignment_operator() {
	std::cout << "=== Test assignment operator ===" << std::endl;
	BitcoinExchange exchange("data_small.csv");
	exchange.showDatabase();

	// Test the assignment operator
	const BitcoinExchange& exchange3 = exchange;
	exchange3.showDatabase();
}

int main(int argc, char **argv) {

	// Check the number of arguments
	if (argc != 2) {
		std::cout << "Usage: ./btc [file]" << std::endl;
		return 1;
	}

	// Execute the program
	BitcoinExchange exchange("data.csv");
	exchange.displayFromFile(argv[1]);

	// Test the copy constructor and the assignment operator
//	std::cout << std::endl;
//	test_copy_constructor();
//	test_assignment_operator();

	return 0;
}
