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



std::vector<int> strToVector(std::string a_str)
{
	std::vector<int> res;
	a_str.erase(std::remove(a_str.begin(), a_str.end(), '['), a_str.end());
	a_str.erase(std::remove(a_str.begin(), a_str.end(), ']'), a_str.end());
	a_str.erase(std::remove(a_str.begin(), a_str.end(), ' '), a_str.end());

	// Разбиваем строку на отдельные числа
	std::istringstream ss(a_str);
	std::string token;
	while (std::getline(ss, token, ',')) {
		res.push_back(std::stoi(token));
	}
	return res;
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

	std::map<std::string, std::string> namespaces = 
	{
		{"main", "mustBeObject"}, 
		{"tmp", "mustBeObject"}
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

		for (auto &subcommand : subcommands)
		{
			// std::string subcommand = command.substr(0, pos);
			std::cout << "подкоманда: " << subcommand << std::endl;
			if (!subcommand.empty())
			{
				if (subcommand.find("routing") != std::string::npos)
				{
					std::string funType = extractToWord(subcommand, "routing");
					std::string funName = extractBetweenWords(subcommand, "routing", "(");
					std::string funParams = extractBetweenWords(subcommand, "(", ")");
					std::string funBody = extractBetweenWords(subcommand, "{", "}");
					std::cout << funType << std::endl;
					std::cout << funName << std::endl;
					std::cout << funParams << std::endl;
					std::cout << funBody << std::endl;
				}
				else if (subcommand.find("digit") != std::string::npos || subcommand.find("logic") != std::string::npos)
				{
					Variable tmp(parseVariableDeclaration(subcommand)), tmp2;
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
				else if (subcommand.find("resize") != std::string::npos)
				{
					std::cout << resize(subcommand, variables);
				}
				else if (subcommand.find("size") != std::string::npos)
				{
					std::cout << getSize(subcommand, variables);
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

					std::cout << printVar(subcommand, variables);
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

					if (res > 0)
					{
						std::cout << "Истина" << res << std::endl;
						std::cout << params[1] << std::endl;
					}
					else
					{
						std::cout << "Ложь" << res << std::endl;
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
					expr.evaluate(subcommand, variables, res);
				}
				else
				{
					std::regex assignRegex(R"((([a-zA-Z_][a-zA-Z0-9_]*)(\[([0-9]+(\s*,\s*[0-9]+)*)\])?))");
					std::smatch match;
					if (std::regex_match(subcommand, match, assignRegex))
					{
						std::cout << printVar(subcommand, variables);
					}
					interpretCommand(subcommand, robot, maze);
				}
			}
		}

		std::cout << ">>> ";
	}

	return 0;
}
