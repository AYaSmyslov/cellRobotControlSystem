#include "Func.h"

Func::Func()
{
}

Func::Func(const std::string &a_funcType, const std::string& a_funcName, const std::string &a_params, const std::string &a_funcBody)
    : _type(a_funcType), _name(a_funcName), _body(a_funcBody)
{
    std::string params = removeSpaces(a_params);
    std::string param;
    if (params != "")
    {
        for (char c : params)
        {
            if (c == ',')
            {
                if (!param.empty())
                {
                    // Variable tmp("digit", param, "[1]", "0");
                    // _variables.push_back(tmp);
                    _parameters.push_back(param);
                    param.clear();
                }
            } else {
                param += c;
            }
            
        }
        _parameters.push_back(param);
    }
}



bool Func::call(const std::string &args, int &a_result)
{

// TODO: добавить учет параметров 
    Expression expr;

    std::string argsConsts = removeSpaces(args);
    std::string arg;
    std::vector<std::string> constValues;

    if (argsConsts != "")
    {
        for (char c : argsConsts)
        {
            if (c == ',')
            {
                if (!arg.empty())
                {
                    constValues.push_back(arg);
                    arg.clear();
                }
            } else {
                arg += c;
            }
        }
        constValues.push_back(arg);
    }
    std::string paramInit;
    for (int i = 0; i < _parameters.size(); i++)
    {
        paramInit += "digit " + _parameters[i] + "=" + constValues[i] + ";";
    }
    _body = paramInit + _body;
    std::vector<std::string> subcommands = split(_body);

    // for (auto &subcommands[commInd] : subcommands)
    for (int commInd=0; commInd < subcommands.size(); commInd++)
    {
        // std::string subcommands[commInd] = command.substr(0, pos);
        // std::cout << "подкоманда: " << subcommands[commInd] << std::endl;
        if (!subcommands[commInd].empty())
        {
            if (subcommands[commInd].find("digit") != std::string::npos || subcommands[commInd].find("logic") != std::string::npos)
            {
                Variable tmp(parseVariableDeclaration(subcommands[commInd])), tmp2;
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
            else if (subcommands[commInd].find("resize") != std::string::npos)
            {
                std::cout << resize(subcommands[commInd], _variables);
            }
            else if (subcommands[commInd].find("size") != std::string::npos)
            {
                std::cout << getSize(subcommands[commInd], _variables);
            }
            else if (subcommands[commInd].find("return") != std::string::npos)
            {
                std::string ret = extractFromWord(subcommands[commInd], "return");
                ret = removeSpaces(ret);
                std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
                std::regex integerPattern(R"(^-?\d+$)");
                std::smatch match;
                if (std::regex_match(ret, match, assignRegex))
                {
                    a_result = std::stoi(printVar(ret, _variables));
                }
                if (std::regex_match(ret, match, integerPattern))
                {
                    a_result = std::stoi(ret);
                }
                return true;
                std::cout << printVar(subcommands[commInd], _variables);
            }
            else if (subcommands[commInd].find("print") != std::string::npos)
            {

                const std::string start = "print(";
                const std::string end = ")";

                if (subcommands[commInd].size() >= start.size() + end.size() &&
                    subcommands[commInd].substr(0, start.size()) == start &&
                    subcommands[commInd].substr(subcommands[commInd].size() - end.size(), end.size()) == end)
                {
                    subcommands[commInd] = subcommands[commInd].substr(start.size(), subcommands[commInd].size() - start.size() - end.size());
                }

                std::cout << printVar(subcommands[commInd], _variables);
            }
            else if (subcommands[commInd].find("check") != std::string::npos && subcommands[commInd].find("then") != std::string::npos) 
            {
                
                std::vector<std::string> params;
                bool haveElse = false;
                params.push_back(extractBetweenWords(subcommands[commInd], "check", "then"));
                params.push_back(extractBetweenWords(subcommands[commInd], "then {", "}"));
                if (subcommands[commInd].find("overwise") != std::string::npos)
                {
                    std::string tmp = extractFromWord(subcommands[commInd], "overwise {");
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

                std::string loopedAlg = "";
					if (res > 0)
					{
						loopedAlg+=params[1];
					}
					else
					{
						if (haveElse)
						{
							loopedAlg+=params[2];
						}
					}
					std::vector<std::string> resAlg = split(loopedAlg);
					for (auto oResAlg : resAlg)
					{
						subcommands.push_back(oResAlg);
					}
            }
            else if (subcommands[commInd].find("for") != std::string::npos && subcommands[commInd].find("stop") != std::string::npos && subcommands[commInd].find("step") != std::string::npos) 
            {
                std::vector<std::string> params;
                params.push_back(extractBetweenWords(subcommands[commInd], "for", "stop"));
                params.push_back(extractBetweenWords(subcommands[commInd], "stop", "step"));
                params.push_back(extractBetweenWords(subcommands[commInd], "step", "{"));
                std::string loopedAlg = "";
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
                        while (counter[i] < boundary[i])
                        {
                            std::cout << i << " ";
                            counter[i] += step[i];
                            loopedAlg+=params[3];
                        }
                    }
                    else
                    {
                        while (counter[i] > boundary[i])
                        {
                            std::cout << i << " ";
                            counter[i] += step[i];
                            loopedAlg+=params[3];
                        }
                    }
                    
                    std::cout << std::endl;
                }
                

                std::vector<std::string> resAlg = split(loopedAlg);
                for (auto oResAlg : resAlg)
                {
                    subcommands.push_back(oResAlg);
                }
            }
            else if (expr.isExpression(subcommands[commInd]))
            {
                int res;
                expr.evaluate(subcommands[commInd], _variables, res);
            }
            else
            {
                std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
                std::smatch match;
                if (std::regex_match(subcommands[commInd], match, assignRegex))
                {
                    std::cout << printVar(subcommands[commInd], _variables);
                }
            }
        }
    }
    return false;
}