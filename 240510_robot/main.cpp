#include <stdio.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "Variable.h"
#include "commands.h"
#include "Robot.h"
#include "Func.h"



// Определение структуры лабиринта
struct Maze
{
	std::vector<std::vector<int>> grid; // сетка лабиринта
	// ... другие свойства и методы ...
};



// Функция для интерпретации команд
void interpretCommand(const std::string &command, Robot &robot, Maze &maze)
{
	// ... реализация ...
}



int main(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		const char *arg = argv[i];
		if (!strcmp(arg, "--help"))
		{
			puts(R"(
240510_robot - is very useful utility
)");
			return 0;
		}
	}

	Robot robot;
	Maze maze;

	std::map<std::string, Func> namespaces = 
	{
		{"main", Func()}, 
		{"tmp", Func()}
	};

	std::string command;
	std::vector<Variable> variables;

	Expression expr;

	std::cout << ">>> ";
	while (std::getline(std::cin, command))
	{
		std::cout << "Вы ввели: " << command << std::endl;
		if (command == "exit" || command == "q")
		{
			break;
		}

		std::vector<std::string> subcommands = split(command);

		// for (auto &subcommands[commInd] : subcommands)
		for (int commInd=0; commInd < subcommands.size(); commInd++)
		{
			
			// std::string subcommands[commInd] = command.substr(0, pos);
			// std::cout << "подкоманда: " << subcommands[commInd] << std::endl;
			if (!subcommands[commInd].empty())
			{
				if (subcommands[commInd].find("routing") != std::string::npos)
				{
					std::string funType = extractToWord(subcommands[commInd], "routing");
					std::string funName = extractBetweenWords(subcommands[commInd], "routing", "(");
					std::string funParams = extractBetweenWords(subcommands[commInd], "(", ")");
					std::string funBody = extractBetweenWords(subcommands[commInd], "{", "}");
					std::cout << funType << std::endl;
					std::cout << funName << std::endl;
					std::cout << funParams << std::endl;
					std::cout << funBody << std::endl;
					namespaces[funName] = Func(funType, funName, funParams, funBody);
				}
				else if (subcommands[commInd].find("perform") != std::string::npos)
				{
					std::cout << "вызов" << std::endl;
					std::string varName = extractToWord(subcommands[commInd], "perform");
					std::string funName = extractBetweenWords(subcommands[commInd], "perform", "(");
					std::string funParams = extractBetweenWords(subcommands[commInd], "(", ")");
					std::cout << funName << std::endl;
					std::cout << funParams << std::endl;
					int result=0;
					if (namespaces[funName].call(funParams, result))
					{
						// есть возврат
						if (varName != "")
						{
							varName = removeSpaces(varName);
							// varName = extractToWord(varName, "=");
							std::string alg = varName + std::to_string(result) + ";";
							subcommands.push_back(alg);
							
						}
					}
					else
					{
						// без возврата
					}
				}
				else if (subcommands[commInd].find("digit") != std::string::npos || subcommands[commInd].find("logic") != std::string::npos)
				{
					Variable tmp(parseVariableDeclaration(subcommands[commInd])), tmp2;
					if (findVariable(tmp.getName(), variables, tmp2))
					{
						auto it = std::find_if(variables.begin(), variables.end(), [&](const Variable &var)
												{
													return var.getName() == tmp2.getName();
												});
						if (it != variables.end())
						{
							variables.erase(it);
						}
					}
					variables.push_back(tmp);
					variables.back().print();
				}
				else if (subcommands[commInd].find("resize") != std::string::npos)
				{
					std::cout << resize(subcommands[commInd], variables);
				}
				else if (subcommands[commInd].find("size") != std::string::npos)
				{
					std::cout << getSize(subcommands[commInd], variables);
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

					std::cout << printVar(subcommands[commInd], variables);
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
						expr.evaluate(params[0], variables, res);
					}
					else
					{
						params[0].erase(std::remove(params[0].begin(), params[0].end(), ' '), params[0].end());
						std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
						std::regex integerPattern(R"(^-?\d+$)");
						std::smatch match;
						if (std::regex_match(params[0], match, assignRegex))
						{
							res = std::stoi(printVar(params[0], variables));
						}
						if (std::regex_match(params[0], match, integerPattern))
						{
							res = std::stoi(params[0]);
						}
					}

					std::string loopedAlg = "";
					if (res > 0)
					{
						std::cout << "Истина" << res << std::endl;
						std::cout << params[1] << std::endl;
						loopedAlg+=params[1];
					}
					else
					{
						std::cout << "Ложь" << res << std::endl;
						if (haveElse)
						{
							std::cout << params[2] << std::endl;
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
					params.push_back(extractBetweenWords(subcommands[commInd], "{", "}"));
					std::string loopedAlg = "";
					for (int i=0; i < params.size()-1; i++)
					{
						if (std::regex_search(params[i].cbegin(), params[i].cend(), expr.variable_re))
						{
							expr.replaceVarToConst(params[i], variables);
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
					

					std::cout << params[0] << '\t' << params[1] << '\t' << params[2] << std::endl;

					std::vector<std::string> resAlg = split(loopedAlg);
					for (auto oResAlg : resAlg)
					{
						subcommands.push_back(oResAlg);
					}

				}
				else if (expr.isExpression(subcommands[commInd]))
				{
					int res;
					expr.evaluate(subcommands[commInd], variables, res);
				}
				else
				{
					std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
					std::smatch match;
					if (std::regex_match(subcommands[commInd], match, assignRegex))
					{
						std::cout << printVar(subcommands[commInd], variables);
					}
					interpretCommand(subcommands[commInd], robot, maze);
				}
			}
		}

		std::cout << ">>> ";
	}

	return 0;
}
