#include "Expression.h"
#include "commands.h"
// #include "Parser.h"

// в комментариях справка по группам каждого выражения
Expression::Expression()
	:
	_assign_re(R"(([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?\s*=\s*(.+))"), // [0: "fullstr", 1: "varname", 2: "[indexes]", 3: "indexes", 4: ", index", 5: "expression"]
	_variable_re(R"(([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?)"), // поиск переменных
	_most_re(R"(^most\((\d+)\)$)"),
	_not_re(R"(^!\((\d+)\)$)"),
	_and_re(R"(^(\d+)\s*&&\s*(\d+)$)"),
	_eq_re(R"(^eq\((\d+)\)$)"), // рудимент
	_lt_re(R"(^lt\((\d+)\)$)"), // рудимент
	_gt_re(R"(^gt\((\d+)\)$)"), // рудимент
	_lte_re(R"(^lte\((\d+)\)$)"), // рудимент
	_gte_re(R"(^gte\((\d+)\)$)"), // рудимент
	_cmpZero_re(R"(^(eq|lt|gt|lte|gte)\((\d+)\)$)"), // [0: "fullstr", 1: "operator name", 2: "const"]
	_op_re(R"(((most|!|eq|lt|gt|lte|gte)\((\d+)\))|((\d+)\s*&&\s*(\d+)))") // [0: "fullstr", 1: "operator name", 2: "const"]
{

}



Expression::~Expression()
{
}



bool Expression::isExpression(const std::string &a_expr) const
{
	for (auto oOp : _ops)
	{
		if (a_expr.find(oOp) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}



bool Expression::evaluate(std::string &a_expr, std::vector<Variable> &a_variables)
{
	_variables = a_variables;
	std::smatch match;

	if (std::regex_match(a_expr, match, _assign_re))
	{
		std::string expAssign = match[1];
		std::string expNoAssign = match[5];
		if (evaluate(expNoAssign, a_variables))
		{
			std::cout << "Будет присвоено: " << expNoAssign << std:: endl; // dbg

            Parser parser(expNoAssign); 
            double result = parser.parse(); // Вычислить арифметическое выражение

            std::cout << "Посчитано: " << result << std::endl;

            Variable tmp2;
            if (findVariable(expAssign, a_variables, tmp2))
            {
                auto it = std::find_if(a_variables.begin(), a_variables.end(), [&](const Variable &var)
                                        {
                                            return var.getName() == tmp2.getName();
                                        });
                if (it != a_variables.end())
                {
                    it->setValue({int(result)}, {1});
                }
            }

			return true;
		}
	}

	// заменить имена переменных на константы
	if (std::regex_search(a_expr.cbegin(), a_expr.cend(), _variable_re))
	{
		_replaceVarToConst(a_expr);
	}

	// Вычисления
	_parseOp(a_expr);



	return true;
}



std::vector<int> Expression::parseNumbers(const std::string& input) {
	std::vector<int> numbers;
	std::stringstream ss(input);
	std::string item;

	while (std::getline(ss, item, ',')) {
		numbers.push_back(std::stoi(item));
	}

	return numbers;
}



bool Expression::most(const std::vector<int>& numbers) {
	int count_non_zero = 0;
	for (int number : numbers) {
		if (number != 0) {
			count_non_zero++;
		}
	}
	return count_non_zero > numbers.size() / 2;
}



template <typename Predicate>
bool Expression::check_majority(const std::vector<int>& data, Predicate pred)
{
	int count = std::count_if(data.begin(), data.end(), pred);
	return count > data.size() / 2;
}



/*
eq, lt, gt, lte, gte
operator(expression)
*/
int Expression::cmpZero(const std::string &a_op, const std::vector<int>& a_data)
{
	if (a_op == "eq")
	{
		return (int)check_majority(a_data, [](int x) { return x == 0; });
	} else if (a_op == "lt") {
		return (int)check_majority(a_data, [](int x) { return x < 0; });
	} else if (a_op == "gt") {
		return (int)check_majority(a_data, [](int x) { return x > 0; });
	} else if (a_op == "lte") {
		return (int)check_majority(a_data, [](int x) { return x <= 0; });
	} else if (a_op == "gte") {
		return (int)check_majority(a_data, [](int x) { return x >= 0; });
	} else {
		std::cerr << "Unknown operator: " << a_op << std::endl;
		return -1;
	}
}


// Заменить все переменные на их значения
bool Expression::_replaceVarToConst(std::string &a_expr)
{
	std::string varParsedExpr;
	std::string::const_iterator searchStart(a_expr.cbegin());
	varParsedExpr.reserve(a_expr.size());
	std::smatch match;
	while (std::regex_search(searchStart, a_expr.cend(), match, _variable_re))
	{
		std::string word = match.str();
		if (_isReservedWord(word))
		{
			varParsedExpr.append(searchStart, match[0].first);
			varParsedExpr.append(word);
		}
		else
		{
			varParsedExpr.append(searchStart, match[0].first);
			varParsedExpr.append(printVar(match[0], _variables));
		}
		searchStart = match.suffix().first;
	}
	varParsedExpr.append(searchStart, a_expr.cend());

	std::cout << "Подстановка констант: " << varParsedExpr << std::endl; // dbg
	varParsedExpr.erase(std::remove(varParsedExpr.begin(), varParsedExpr.end(), ' '), varParsedExpr.end());

	a_expr = varParsedExpr;

	return true;
}


// Заменить все операторы на их значения
bool Expression::_parseOp(std::string &a_expr)
{
	std::smatch match;
	std::string temp = a_expr;
	std::string op;
	while (std::regex_search(temp, match, _op_re))
	{
		op = match.str();
		if (!_executeOp(op)) {return false;}
        a_expr.replace(match.position(), match.length(), op);
		temp = a_expr;
	}
	return true;
}


// Вызов оператора
bool Expression::_executeOp(std::string &a_expr)
{
	std::smatch match;
	if (std::regex_match(a_expr, match, _most_re))
	{
		a_expr = std::to_string(most({stoi(a_expr)})); // функция поддерживает многомерные значения, но не используется
		return true;
	}
	if (std::regex_match(a_expr, match, _not_re))
	{
		a_expr = std::to_string(!stoi(match[1]));
		return true;
	}
	if (std::regex_match(a_expr, match, _cmpZero_re))
	{
		a_expr = std::to_string(cmpZero(match[1], {stoi(match[2])})); // функция поддерживает многомерные значения, но не используется
		return true;
	}
	if (std::regex_match(a_expr, match, _and_re))
	{
		int const1 = std::stoi(match[1]);
		int const2 = std::stoi(match[2]);
		a_expr = std::to_string((const1 && const2));
		return true;
	}
	return false;
}

// Проверить является ли слово служебным 
bool Expression::_isReservedWord(const std::string &a_word)
{
	return std::find(_ops.begin(), _ops.end(), a_word) != _ops.end();
}


bool evaluateArithmetic()
{
	return true;
}
