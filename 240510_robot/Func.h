#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <regex>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Variable.h"
#include "commands.h"

class Func
{
public:
    std::string _type;
    std::string _name;
    std::vector<std::string> _parameters;
    std::vector<Variable> _variables;
    // std::vector<std::string> body;
    std::string _body;


    Func();

    Func(const std::string &a_funcType, const std::string& a_funcName, const std::string &a_params, const std::string &a_funcBody);

    bool call(const std::string &args, int &a_result);
};