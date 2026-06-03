#include <iostream>
#include <sstream> 
#include <string>
#include <list>
#include <stack>
#include <climits>

enum charType
{
	OPERATOR,
	OPERAND,
	INVALID
};

charType	evaluateChar(const char c)
{
	const std::string allowed = "+-/*";

	if (allowed.find (c, 0) != std::string::npos)
		return (OPERATOR);
	else if (c >= '0' && c <= '9')
		return (OPERAND);
	else
		return (INVALID);
}

int	errorCode(const std::string &msg, const int code)
{
	std::cerr << msg << std::endl;
	return (code);
}

int	executeOperation(const char c, int a, int b)
{
	long long	result;

	switch (c)
	{
		case '+':
			result = static_cast<long long >(a) + b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error ("Int overflow");
			return (a + b);
		case '-':
			result = static_cast<long long >(a) - b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error ("Int overflow");
			return (a - b);
		case '*':
			result = static_cast<long long >(a) * b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error ("Int overflow");
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error ("Division by 0");
			return (a / b);
		default:
			throw std::runtime_error ("Invalid operator");
	}
}

int	RPN(const std::string &input)
{
	std::istringstream sstream (input);
	std::string token;
	bool emptyString = true;

	std::stack<int, std::list<int> > myStack;

	while (sstream >> token)
	{
		emptyString = false;
		if (token.size () != 1)
			return (errorCode ("Error", 2));

		char c = token[0];
		charType type = evaluateChar (c);

		switch (type)
		{
			case INVALID:
				return (errorCode ("Error", 2));

			case OPERATOR:
			{
				if (myStack.empty ())
					return (errorCode ("Error", 3));

				int b = myStack.top ();
				myStack.pop ();
				if (myStack.empty ())
					return (errorCode ("Error", 3));

				int a = myStack.top ();
				myStack.pop ();

				try { myStack.push (executeOperation (c, a, b)); }
				catch (std::exception) { return (errorCode ("Error", 3));};
				break;
			}

			case OPERAND:
				myStack.push (c - '0');
				break;
		}
	}

	if (emptyString)
		return (errorCode ("Error", 2));

	if (myStack.size () != 1)
		return (errorCode ("Error", 4));

	std::cout << myStack.top () << "\n" ;

	return (0);
}