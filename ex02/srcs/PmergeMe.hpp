#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <algorithm>
# include <sstream>

#define DEBUG 1

class PmergeMe
{
	public:
		PmergeMe(); // default constructor
		~PmergeMe(); // destructor
		PmergeMe(PmergeMe const &src); // copy constructor
		PmergeMe &operator=(PmergeMe const &rhs); // copy assignment operator

		void	createVector(char **argv);
		void	printVector(const std::string& title) const;
		void	sortVector();

		static bool	isValid(char **argv, bool checkDuplicate);
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;
};

class Pair
{
	public:
		Pair(int first, int second) : _first(first), _second(second) {}
		~Pair() {}
		Pair(Pair const &src) {
			*this = src;
		}
		Pair &operator=(Pair const &rhs) {
			if (this != &rhs) {
				_first = rhs._first;
				_second = rhs._second;
			}
			return *this;
		}

		int		_first;
		int		_second;
};

#endif