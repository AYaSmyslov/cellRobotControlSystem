#include <stdio.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>

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
		if (command.find(';') != std::string::npos)
		{
			std::size_t pos = 0;
			std::string delimiter = ";";
			while ((pos = command.find(delimiter)) != std::string::npos)
			{
				std::string subcommand = command.substr(0, pos);
				if (!subcommand.empty())
				{
					if (subcommand.find("digit") != std::string::npos || subcommand.find("logic") != std::string::npos)
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
					else if (expr.isExpression(subcommand))
					{
						expr.evaluate(subcommand, variables);
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
				command.erase(0, pos + delimiter.length());
			}
		}

		std::cout << ">>> ";
	}

	return 0;
}
