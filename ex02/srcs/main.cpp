
#include <iostream>
#include "PmergeMe.hpp"

//static void	test_copy_constructor(char **argv) {
//	std::cout << "=== test_copy_constructor ===" << std::endl;
//	PmergeMe list;
//	list.createList(argv);
//	list.printList("Original list");
//	PmergeMe listCopy(list);
//	listCopy.printList("Copy list");
//
//	PmergeMe vector;
//	vector.createVector(argv);
//	vector.printVector("Original vector");
//	PmergeMe vectorCopy(vector);
//	vectorCopy.printVector("Copy vector");
//
//	std::cout << std::endl;
//}
//
//static void	test_copy_assignment_operator(char **argv) {
//	std::cout << "=== test_copy_assignment_operator ===" << std::endl;
//	PmergeMe list;
//	list.createList(argv);
//	list.printList("Original list");
//	PmergeMe listCopy;
//	listCopy = list;
//	listCopy.printList("Copy list");
//
//	PmergeMe vector;
//	vector.createVector(argv);
//	vector.printVector("Original vector");
//	PmergeMe vectorCopy;
//	vectorCopy = vector;
//	vectorCopy.printVector("Copy vector");
//	std::cout << std::endl;
//}
//
//static void	tests(char **argv) {
//	test_copy_constructor(argv);
//	test_copy_assignment_operator(argv);
//}

static void	printTime(int nNumber, double elapsedTime, const std::string& container) {
	std::cout << std::fixed << "Time to process a range of " << nNumber << " elements with std::[" << container << "] : "  << elapsedTime << " us" << std::endl;
}

static	void	pmergeme(int argc, char **argv) {
	// List
	PmergeMe pmergeMeList;
	pmergeMeList.createList(argv);
	pmergeMeList.printList("Before");
	const clock_t beginTimeList = clock();
	pmergeMeList.sortList();
	const double elapsedTimeList = double(clock() - beginTimeList) / CLOCKS_PER_SEC;
	pmergeMeList.printList("After");
	printTime(argc - 1, elapsedTimeList, "list");

	// Vector
	PmergeMe pmergeMeVector;
	pmergeMeVector.createVector(argv);
//	pmergeMeVector.printVector("Before");
	const clock_t beginTimeVector = clock();
	pmergeMeVector.sortVector();
	const double elapsedTimeVector = double(clock() - beginTimeVector) / CLOCKS_PER_SEC;
//	pmergeMeVector.printVector("After");
	printTime(argc - 1, elapsedTimeVector, "vector");
}

int main(int argc, char **argv) {

	if (argc < 3) {
		std::cout << "Usage: ./PmergeMe <number> <number> ..." << std::endl;
		return 1;
	}

	if (!PmergeMe::isValid(argv, false))
		return 1;

	// PmergeMe
	pmergeme(argc, argv);

	// Tests
//	(void)argc;
//	tests(argv);

	return 0;
}
