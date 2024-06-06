#include "Func.h"

Func::Func()
{
}

Func::Func(const std::string &a_funcType, const std::string& a_funcName, const std::string &a_params, const std::string &a_funcBody)
    : _type(a_funcType), _name(a_funcName), _body(a_funcBody)
{
    std::string params = removeSpaces(a_params);
    std::string param;
    for (char c : params)
    {
        if (c == ',')
        {
            if (!param.empty())
            {
                Variable tmp("digit", param, "[1]", "0");
                _variables.push_back(tmp);
                _parameters.push_back(param);
                param.clear();
            }
        } else {
            param += c;
        }
    }
    
}



void Func::call(const std::string &args)
{

// TODO: добавить учет параметров 
    Expression expr;
    std::vector<std::string> subcommands = split(_body);

    for (auto &subcommand : subcommands)
    {
        // std::string subcommand = command.substr(0, pos);
        // std::cout << "подкоманда: " << subcommand << std::endl;
        if (!subcommand.empty())
        {
            if (subcommand.find("digit") != std::string::npos || subcommand.find("logic") != std::string::npos)
            {
                Variable tmp(parseVariableDeclaration(subcommand)), tmp2;
                if (findVariable(tmp.getName(), _variables, tmp2))
                {
                    auto it = std::find_if(_variables.begin(), _variables.end(), [&](const Variable &var)
                                            {
                                                return var.getName() == tmp2.getName();
                                            });
                    if (it != _variables.end())
                    {
                        _variables.erase(it);
                    }
                }
                _variables.push_back(tmp);
                _variables.back().print();
            }
            else if (subcommand.find("resize") != std::string::npos)
            {
                std::cout << resize(subcommand, _variables);
            }
            else if (subcommand.find("size") != std::string::npos)
            {
                std::cout << getSize(subcommand, _variables);
            }
            else if (subcommand.find("return") != std::string::npos)
            {

                // const std::string start = "return ";
                // // const std::string end = ")";

                // if (subcommand.size() >= start.size() &&
                //     subcommand.substr(0, start.size()) == start &&
                //     subcommand.substr(subcommand.size() - end.size(), end.size()) == end)
                // {
                //     subcommand = subcommand.substr(start.size(), subcommand.size() - start.size() - end.size());
                // }

                std::cout << printVar(subcommand, _variables);
            }
            else if (subcommand.find("print") != std::string::npos)
            {

                const std::string start = "print(";
                const std::string end = ")";

                if (subcommand.size() >= start.size() + end.size() &&
                    subcommand.substr(0, start.size()) == start &&
                    subcommand.substr(subcommand.size() - end.size(), end.size()) == end)
                {
                    subcommand = subcommand.substr(start.size(), subcommand.size() - start.size() - end.size());
                }

                std::cout << printVar(subcommand, _variables);
            }
            else if (subcommand.find("check") != std::string::npos && subcommand.find("then") != std::string::npos) 
            {
                
                std::vector<std::string> params;
                bool haveElse = false;
                params.push_back(extractBetweenWords(subcommand, "check", "then"));
                params.push_back(extractBetweenWords(subcommand, "then {", "}"));
                if (subcommand.find("overwise") != std::string::npos)
                {
                    std::string tmp = extractFromWord(subcommand, "overwise {");
                    tmp.pop_back();
                    params.push_back(tmp);
                    haveElse = true;
                }
                int res;
                if (expr.isExpression(params[0]))
                {
                    expr.evaluate(params[0], _variables, res);
                }
                else
                {
                    params[0].erase(std::remove(params[0].begin(), params[0].end(), ' '), params[0].end());
                    std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
                    std::regex integerPattern(R"(^-?\d+$)");
                    std::smatch match;
                    if (std::regex_match(params[0], match, assignRegex))
                    {
                        res = std::stoi(printVar(params[0], _variables));
                    }
                    if (std::regex_match(params[0], match, integerPattern))
                    {
                        res = std::stoi(params[0]);
                    }
                }

                if (res > 0)
                {
                    std::cout << params[1] << std::endl;
                }
                else
                {
                    if (haveElse)
                    {
                    std::cout << params[2] << std::endl;
                    }
                }
            }
            else if (subcommand.find("for") != std::string::npos && subcommand.find("stop") != std::string::npos && subcommand.find("step") != std::string::npos) 
            {
                std::vector<std::string> params;
                params.push_back(extractBetweenWords(subcommand, "for", "stop"));
                params.push_back(extractBetweenWords(subcommand, "stop", "step"));
                params.push_back(extractBetweenWords(subcommand, "step", "{"));

                for (int i=0; i < params.size(); i++)
                {
                    if (std::regex_search(params[i].cbegin(), params[i].cend(), expr.variable_re))
                    {
                        expr.replaceVarToConst(params[i], _variables);
                    }
                }

                std::vector<int> counter = strToVector(params[0]);
                std::vector<int> boundary = strToVector(params[1]);
                std::vector<int> step = strToVector(params[2]);

                // выполнение цикла
                for (int i=0; i < counter.size(); i++)
                {   
                    if (step[i] > 0)
                    {
                        while (counter[i] < boundary[i]) {
                            std::cout << i << " ";
                            counter[i] += step[i];
                        }
                    }
                    else
                    {
                        while (counter[i] > boundary[i]) {
                            std::cout << i << " ";
                            counter[i] += step[i];
                        }
                    }
                    
                    std::cout << std::endl;
                }
                

                std::cout << params[0] << '\t' << params[1] << '\t' << params[2] << std::endl;
            }
            else if (expr.isExpression(subcommand))
            {
                int res;
                expr.evaluate(subcommand, _variables, res);
            }
            else
            {
                std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
                std::smatch match;
                if (std::regex_match(subcommand, match, assignRegex))
                {
                    std::cout << printVar(subcommand, _variables);
                }
            }
        }
    }
}