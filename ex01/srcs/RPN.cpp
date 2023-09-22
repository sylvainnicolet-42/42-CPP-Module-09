
#include "RPN.hpp"

// Prototypes
static bool	isOperator(char c);
static bool	isValid(const std::string& str);

RPN::RPN() {}

RPN::RPN(const std::string& str) {
	if (!isValid(str))
		return;
	this->addToStack(str);
}

RPN::~RPN() {}

RPN::RPN(RPN const &src) {
	*this = src;
}

RPN &RPN::operator=(RPN const &rhs) {
	if (this != &rhs) {
		this->_stack = rhs._stack;
	}
	return *this;
}

void	RPN::run() const {
	if (this->_stack.size() == 1)
		std::cout << this->_stack.top() << std::endl;
}

void	RPN::addToStack(const std::string& str) {
	size_t i = 0;
	while (i < str.length()) {
		if (str[i] == ' ') {
			i++;
			continue;
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if (this->_stack.size() < 2) {
				std::cout << "Error: not enough numbers" << std::endl;
				// clear stack
				while (!this->_stack.empty())
					this->_stack.pop();
				return;
			}
			int a = this->_stack.top();
			this->_stack.pop();
			int b = this->_stack.top();
			this->_stack.pop();
			if (str[i] == '+') {
				this->_stack.push(b + a);
			} else if (str[i] == '-') {
				this->_stack.push(b - a);
			} else if (str[i] == '*') {
				this->_stack.push(b * a);
			} else if (str[i] == '/') {
				this->_stack.push(b / a);
			}
		} else {
			this->_stack.push(std::stoi(str.substr(i)));
		}
		i++;
	}
}

static bool	isOperator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

static bool	isValid(const std::string& str) {
	// Must not contain only spaces
	if (str.find_first_not_of(' ') == std::string::npos) {
		std::cout << "Error: empty string" << std::endl;
		return false;
	}

	// Must contain only digits, operators (+, -, *, /) and spaces
	if (str.find_first_not_of("0123456789+-*/ ") != std::string::npos) {
		std::cout << "Error: invalid character" << std::endl;
		return false;
	}

	// Must contain at least 1 operator
	if (str.find_first_of("+-*/") == std::string::npos) {
		std::cout << "Error: no operator" << std::endl;
		return false;
	}

	// Must be at least 3 characters long
	if (str.length() < 5) {
		std::cout << "Error: format must be \"x x x\"" << std::endl;
		return false;
	}

	// Last character must be an operator
	if (!isOperator(str[str.length() - 1])) {
		std::cout << "Error: last character must be an operator" << std::endl;
		return false;
	}

	// Must have correct format (x x x x x)
	for (size_t i = 0; i < str.length(); i++) {
		if (i % 2 == 0) {
			// if it's not a number or operator
			if (!isdigit(str[i]) && !isOperator(str[i])) {
				std::cout << "Error: format must be \"x x x\"" << std::endl;
				return false;
			}
		} else {
			// if it's not a space
			if (str[i] != ' ') {
				std::cout << "Error: format must be \"x x x\"" << std::endl;
				return false;
			}
		}
	}

	return true;
}