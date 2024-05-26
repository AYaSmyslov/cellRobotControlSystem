#pragma once

#include <string>
#include <regex>
#include <vector>
#include <algorithm>

#include "Variable.h"


class Expression
{
public:
	Expression();
	~Expression();

	bool isExpression(const std::string& a_expr) const;
	bool evaluate(std::string &a_expr, std::vector<Variable> &a_variables);

	std::vector<int> parseNumbers(const std::string& input);
	bool most(const std::vector<int>& numbers);
	template <typename Predicate>
	bool check_majority(const std::vector<int>& data, Predicate pred);
	int cmpZero(const std::string &a_op, const std::vector<int>& a_data);

private:
	bool _replaceVarToConst(std::string &a_expr);
	bool _parseOp(std::string &a_expr);
	bool _executeOp(std::string &a_expr);
	bool _isReservedWord(const std::string& a_word);

	std::regex _most_re;
	std::regex _not_re;
	std::regex _and_re;
	std::regex _eq_re;
	std::regex _lt_re;
	std::regex _gt_re;
	std::regex _lte_re;
	std::regex _gte_re;
	std::regex _assign_re;
	std::regex _variable_re;
	std::regex _cmpZero_re;
	std::regex _op_re;

	std::vector<Variable> _variables;
	std::string _expr;
	std::vector<std::string> _ops {"=", "eq", "lt", "gt", "lte", "gte", "!", "&&", "most", "+", "-", "*", "/"};
};

