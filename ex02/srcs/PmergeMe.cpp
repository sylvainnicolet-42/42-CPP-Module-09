#include "PmergeMe.hpp"

/* PROTYPES */
static std::list<int> merge(std::list<int> A, std::list<int> B);
static std::vector<int> merge(std::vector<int> A, std::vector<int> B);
static std::list<int> fordJohnson(std::list<int> arr);
static std::vector<int> fordJohnson(std::vector<int> arr);

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	if (this != &rhs) {
		_vector = rhs._vector;
		_list = rhs._list;
	}
	return *this;
}

void	PmergeMe::createList(char **argv) {
	for (int i = 1; argv[i]; i++)
		_list.push_back(atoi(argv[i]));
}

void	PmergeMe::createVector(char **argv) {
	for (int i = 1; argv[i]; i++)
		_vector.push_back(atoi(argv[i]));
}

void PmergeMe::printList(const std::string& title) const {
	std::cout << title << ": ";
	for (std::list<int>::const_iterator it = _list.begin(); it != _list.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printVector(const std::string& title) const {
	std::cout << title << ": ";
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::sortList() {
	_list = fordJohnson(_list);
}

void	PmergeMe::sortVector() {
	_vector = fordJohnson(_vector);
}

/* UTILS FUNCTIONS */

static std::list<int> merge(std::list<int> A, std::list<int> B) {
	std::list<int> merged;
	std::list<int>::iterator itA = A.begin();
	std::list<int>::iterator itB = B.begin();

	while (itA != A.end() && itB != B.end()) {
		if (*itA < *itB) {
			merged.push_back(*itA);
			itA++;
		} else {
			merged.push_back(*itB);
			itB++;
		}
	}

	// Ajoute les éléments restants de A et B
	while (itA != A.end()) {
		merged.push_back(*itA);
		itA++;
	}

	while (itB != B.end()) {
		merged.push_back(*itB);
		itB++;
	}

	return merged;
}

static std::vector<int> merge(std::vector<int> A, std::vector<int> B) {
	std::vector<int> merged;
	size_t i = 0, j = 0;

	while (i < A.size() && j < B.size()) {
		if (A[i] < B[j]) {
			merged.push_back(A[i]);
			i++;
		} else {
			merged.push_back(B[j]);
			j++;
		}
	}

	// Ajoute les éléments restants de A et B
	while (i < A.size()) {
		merged.push_back(A[i]);
		i++;
	}

	while (j < B.size()) {
		merged.push_back(B[j]);
		j++;
	}

	return merged;
}

std::list<int>	fordJohnson(std::list<int> arr) {
	if (arr.size() <= 1) {
		return arr;
	}

	// Divisez le tableau en deux sous-tableaux
	size_t middle = arr.size() / 2;
	std::list<int> left;
	std::list<int> right;
	std::list<int>::iterator it = arr.begin();
	for (size_t i = 0; i < middle; i++) {
		left.push_back(*it);
		it++;
	}
	for (size_t i = middle; i < arr.size(); i++) {
		right.push_back(*it);
		it++;
	}

	// Triez récursivement les sous-tableaux
	left = fordJohnson(left);
	right = fordJohnson(right);

	// Fusionnez les sous-tableaux triés
	return merge(left, right);
}

std::vector<int> fordJohnson(std::vector<int> arr) {
	if (arr.size() <= 1) {
		return arr;
	}

	// Divisez le tableau en deux sous-tableaux
	int middle = arr.size() / 2;
	std::vector<int> left(arr.begin(), arr.begin() + middle);
	std::vector<int> right(arr.begin() + middle, arr.end());

	// Triez récursivement les sous-tableaux
	left = fordJohnson(left);
	right = fordJohnson(right);

	// Fusionnez les sous-tableaux triés
	return merge(left, right);
}

/* STATIC FUNCTIONS */

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