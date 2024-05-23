#include "Expression.h"
#include "Parser.h"

Expression::Expression(const std::string& a_expr) 
    : _expr(a_expr),
    _most_re(R"(^most\((.+)\)$)"), // TODO: любой символ принимают!!!
    _not_re(R"(^!(.+)$)"),
    _and_re(R"((.+)\s*&&\s*(.+))"),
    _eq_re(R"(^eq\((.+)\)$)"),
    _lt_re(R"(^lt\((.+)\)$)"),
    _gt_re(R"(^gt\((.+)\)$)"),
    _lte_re(R"(^lte\((.+)\)$)"),
    _gte_re(R"(^gte\((.+)\)$)")
{

}



Expression::~Expression()
{
    
}



bool evaluate()
{
    return true;
}