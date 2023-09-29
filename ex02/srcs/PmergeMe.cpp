#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	if (this != &rhs) {
		_vector = rhs._vector;
		_deque = rhs._deque;
	}
	return *this;
}

// -------------------- VECTOR -------------------- //

void	PmergeMe::createVector(char **argv) {
	for (int i = 1; argv[i]; i++)
		_vector.push_back(atoi(argv[i]));
}

void PmergeMe::printVector(const std::string& title) const {
	std::cout << title << ": ";
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

static int binarySearch(std::vector<int> vector, int right, int element) {
	int left = 0;
	int middle;

	while (left <= right) {
		middle = (left + right) / 2;
		if (element < vector[middle])
			right = middle - 1;
		else if (element > vector[middle])
			left = middle + 1;
		else
			return middle;
	}
	return left;
}

/**
 * Merge-insertion sort performs the following steps, on an input X of n elements:
 * 1. Group the elements of X into [n/2] pairs of elements, arbitrarily, leaving one element unpaired if there is an odd number of elements.
 * 2. Perform [n/2] comparisons, one per pair, to determine the larger of the two elements in each pair.
 * 3. Recursively sort the [n/2] larger elements from each pair, creating a sorted sequence S of [n/2] of the input elements, in ascending order.
 * 4. Insert at the start of S the element that was paired with the first and smallest element of S.
 * 5. Insert the remaining [n/2] - 1 elements of X \ S into S, one at a time.
 *    Use binary search in subsequences of to determine the position at which each element should be inserted.
 */
void	PmergeMe::sortVector() {

	// 1. Group the elements of X into [n/2] pairs of elements, arbitrarily, leaving one element unpaired if there is an odd number of elements.
	if (DEBUG)
		std::cout << std::endl << "=== 1. Group elements into pairs ===" << std::endl;
	std::vector<Pair> pairs;
	int leavedElement = 0;
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it += 2) {
		if (it + 1 == _vector.end()) {
			leavedElement = *it;
			break;
		}
		pairs.push_back(Pair(*it, *(it + 1)));
	}

	// Display pairs
	if (DEBUG) {
		for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
			std::cout << "Pair: [" << it->_first << ", " << it->_second << "]" << std::endl;
		}
	}

	// 2. Perform [n/2] comparisons, one per pair, to determine the larger of the two elements in each pair.
	if (DEBUG)
		std::cout << std::endl << "=== 2. Sort pairs by largest element ===" << std::endl;
	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->_first < it->_second)
			std::swap(it->_first, it->_second);
	}

	// Display pairs
	if (DEBUG) {
		for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
			std::cout << "Pair: [" << it->_first << ", " << it->_second << "]" << std::endl;
		}
	}

	// 3. Sort pairs by first element keeping pairs together
	if (DEBUG)
		std::cout << std::endl << "=== 3. Sort pairs by first element keeping pairs together ===" << std::endl;
	std::vector<Pair> sortedPairs;
	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (sortedPairs.empty()) {
			sortedPairs.push_back(*it);
			continue;
		}
		for (std::vector<Pair>::iterator it2 = sortedPairs.begin(); it2 != sortedPairs.end(); it2++) {
			if (it->_first < it2->_first) {
				sortedPairs.insert(it2, *it);
				break;
			}
			if (it2 + 1 == sortedPairs.end()) {
				sortedPairs.push_back(*it);
				break;
			}
		}
	}

	// Display pairs
	if (DEBUG) {
		for (std::vector<Pair>::iterator it = sortedPairs.begin(); it != sortedPairs.end(); it++) {
			std::cout << "Pair: [" << it->_first << ", " << it->_second << "]" << std::endl;
		}
	}

	// 4. Insert elements into sorted vector using binary search
	if (DEBUG)
		std::cout << std::endl << "=== 4. Insert elements into sorted vector using binary search ===" << std::endl;

	// Insert first pair
	std::vector<int> sortedVector;
	sortedVector.push_back(sortedPairs[0]._second);
	sortedVector.push_back(sortedPairs[0]._first);

	// Insert remaining elements
	for (std::vector<Pair>::iterator it = sortedPairs.begin() + 1; it != sortedPairs.end(); it++) {
		// Insert first element of pair at the end of sorted vector
		sortedVector.push_back(it->_first);

		// Insert second element at correct index using binary search
		int right = sortedVector.size() - 1;
		int index = binarySearch(sortedVector, right, it->_second);
		sortedVector.insert(sortedVector.begin() + index, it->_second);
	}

	// Insert leaved element using binary search
	if (leavedElement) {
		int right = sortedVector.size() - 1;
		int index = binarySearch(sortedVector, right, leavedElement);
		sortedVector.insert(sortedVector.begin() + index, leavedElement);
	}

	// Display sorted vector
	if (DEBUG) {
		std::cout << std::endl << "=== 5. Sorted vector ===" << std::endl;
		for (std::vector<int>::iterator it = sortedVector.begin(); it != sortedVector.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	_vector = sortedVector;
}

// -------------------- VALIDATION -------------------- //

bool PmergeMe::isValid(char **argv, bool checkDuplicate) {
	for (int i = 1; argv[i]; i++) {
		// Contains only digits
		for (int j = 0; argv[i][j]; j++) {
			if (!isdigit(argv[i][j])) {
				std::cout << "Error: invalid input" << std::endl;
				return false;
			}
		}

		// Must be positive
		std::stringstream	ss(argv[i]);
		int					n;

		ss.clear();
		ss >> n;
		if (ss.fail()) {
			std::cout << "Error: MAX_INT overflow" << std::endl;
			return false;
		}
		ss.clear();
		if(n <= 0) {
			std::cout << "Error: invalid input" << std::endl;
			return false;
		}

		// Check for duplicates
		if (checkDuplicate) {
			for (int j = i + 1; argv[j]; j++) {
				if (atoi(argv[i]) == atoi(argv[j])) {
					std::cout << "Error: duplicate input" << std::endl;
					return false;
				}
			}
		}
	}
	return true;
}