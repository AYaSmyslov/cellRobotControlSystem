#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Parser {
public:
	Parser(const std::string& expression);

	double parse();

private:
	std::string expr;
	size_t pos;

	double parseExpression();
	double parseTerm();

	double parseFactor();

	double parseNumber();

	void skipWhitespace();
};
