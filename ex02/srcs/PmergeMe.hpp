#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <algorithm>
# include <sstream>

class PmergeMe
{
	public:
		PmergeMe(); // default constructor
		~PmergeMe(); // destructor
		PmergeMe(PmergeMe const &src); // copy constructor
		PmergeMe &operator=(PmergeMe const &rhs); // copy assignment operator

		void		createList(char **argv);
		void		printList(const std::string& title) const;
		void		sortList();

		void		createVector(char **argv);
		void		printVector(const std::string& title) const;
		void		sortVector();

		static bool	isValid(char **argv, bool checkDuplicate);
	private:
		std::vector<int>	_vector;
		std::list<int>		_list;
};

#endif