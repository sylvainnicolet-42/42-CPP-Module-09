#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>

class RPN
{
	public:
		RPN(const std::string& str); // constructor
		~RPN(); // destructor
		RPN(RPN const &src); // copy constructor
		RPN &operator=(RPN const &rhs); // copy assignment operator

		void run() const;
	private:
		RPN(); // default constructor
		std::stack<int> _stack;

		void addToStack(const std::string& str);
};


#endif