
#include <iostream>
#include "PmergeMe.hpp"

static void	printTime(int nNumber, double elapsedTime, const std::string& container) {
	std::cout << std::fixed << "Time to process a range of " << nNumber << " elements with std::[" << container << "] : "  << elapsedTime << " us" << std::endl;
}

int main(int argc, char **argv) {

	if (argc < 3) {
		std::cout << "Usage: ./PmergeMe <number> <number> ..." << std::endl;
		return 1;
	}

	if (!PmergeMe::isValid(argv, false))
		return 1;

	// Vector
	PmergeMe pmergeMeVector;
	pmergeMeVector.createVector(argv);
	pmergeMeVector.printVector("Before[vector]");
	const clock_t beginTimeVector = clock();
	pmergeMeVector.sortVector();
	const double elapsedTimeVector = double(clock() - beginTimeVector) / CLOCKS_PER_SEC;
	pmergeMeVector.printVector("After[vector]");

	// Deck
	PmergeMe pmergeMeDeque;
	pmergeMeDeque.createDeque(argv);
	pmergeMeDeque.printDeque("Before[deque]");
	const clock_t beginTimeDeque = clock();
	pmergeMeDeque.sortDeque();
	const double elapsedTimeDeque = double(clock() - beginTimeDeque) / CLOCKS_PER_SEC;
	pmergeMeDeque.printDeque("After[deque]");

	printTime(argc - 1, elapsedTimeVector, "vector");
	printTime(argc - 1, elapsedTimeDeque, "deque");

	return 0;
}
