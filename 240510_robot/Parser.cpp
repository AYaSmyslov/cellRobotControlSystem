#include "Parser.h"

Parser::Parser(const std::string& expression) : expr(expression), pos(0) {}

double Parser::parse()
{
	pos = 0;
	return parseExpression();
}



double Parser::parseExpression()
{
	double result = parseTerm();
	while (pos < expr.length())
	{
		if (expr[pos] == '+')
		{
			++pos;
			result += parseTerm();
		}
		else if (expr[pos] == '-')
		{
			++pos;
			result -= parseTerm();
		}
		else
		{
			break;
		}
	}
	return result;
}



double Parser::parseTerm()
{
	double result = parseFactor();
	while (pos < expr.length())
	{
		if (expr[pos] == '*')
		{
			++pos;
			result *= parseFactor();
		}
		else if (expr[pos] == '/')
		{
			++pos;
			double divisor = parseFactor();
			if (divisor == 0)
			{
				throw std::runtime_error("Division by zero");
			}
			result /= divisor;
		}
		else
		{
			break;
		}
	}
	return result;
}



double Parser::parseFactor()
{
	skipWhitespace();
	if (pos < expr.length() && expr[pos] == '(')
	{
		++pos;
		double result = parseExpression();
		if (pos < expr.length() && expr[pos] == ')')
		{
			++pos;
		}
		else
		{
			throw std::runtime_error("Mismatched parentheses");
		}
		return result;
	}
	else
	{
		return parseNumber();
	}
}



double Parser::parseNumber()
{
	skipWhitespace();
	size_t startPos = pos;
	while (pos < expr.length() && (isdigit(expr[pos]) || expr[pos] == '.'))
	{
		++pos;
	}
	if (startPos == pos)
	{
		throw std::runtime_error("Expected number");
	}
	return std::stod(expr.substr(startPos, pos - startPos));
}



void Parser::skipWhitespace()
{
	while (pos < expr.length() && isspace(expr[pos]))
	{
		++pos;
	}
}

//int main() {
//    std::string expression;
//    std::cout << "Enter an arithmetic expression: ";
//    std::getline(std::cin, expression);

//    try {
//        Parser parser(expression);
//        double result = parser.parse();
//        std::cout << "Result: " << result << std::endl;
//    } catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }

//    return 0;
//}

