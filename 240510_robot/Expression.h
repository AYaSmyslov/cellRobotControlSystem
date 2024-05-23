#pragma once

#include <string>
#include <regex>


class Expression
{
public:
    Expression(const std::string& a_expr);
    ~Expression();

    bool evaluate();

private:
    std::regex _most_re;
    std::regex _not_re;
    std::regex _and_re;
    std::regex _eq_re;
    std::regex _lt_re;
    std::regex _gt_re;
    std::regex _lte_re;
    std::regex _gte_re;

    std::string _expr;
};