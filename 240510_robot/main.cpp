#include <stdio.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

#include "Variable.h"
#include "commands.h"
#include "Func.h"

#include "Platform.h"
#include "Robot.h"

// #define COUNT_PLATFORM_LAYERS 2

int mind = 10;



void loadMap(const std::string& filename, std::vector<Platform>& platforms)
{
    std::ifstream infile(filename);
    if (!infile)
	{
        throw std::runtime_error("Unable to open file");
    }

    int q, r, s;
    std::string stateStr;
    while (infile >> q >> r >> s >> stateStr)
	{
        PlatformState state;
        if (stateStr == "free")
		{
            state = FREE;
        } else if (stateStr == "wall")
		{
            state = WALL;
        } else if (stateStr == "exit")
		{
            state = EXIT;
        } else
		{
            throw std::runtime_error("Invalid state in map file");
        }
        platforms.push_back(Platform(q, r, s, state));
    }
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
	std::vector<Platform> platforms;

	std::vector<Platform> directions = {
        Platform(+1, -1,  0), Platform(+1,  0, -1), Platform( 0, +1, -1),
        Platform(-1, +1,  0), Platform(-1,  0, +1), Platform( 0, -1, +1)
    };
	// x + y + z = 0 !!!
	try
	{
        loadMap("map.txt", platforms);
    }
	catch (const std::exception& e)
	{
        std::cerr << "Ошибка загрузки карты: " << e.what() << std::endl;
        return 1;
    }

	// for (int i=0; i < platforms.size();i++)
	// {
	// 	std::cout << i << ": " << platforms[i].getPos()[0] << " " << platforms[i].getPos()[1] << " " << platforms[i].getPos()[2] << " " << platforms[i].getState() << std::endl;
	// }

	int tmpSize = platforms.size()-1;
	int cntLayers = 1;
	int stepSize = 6;
	while (tmpSize > 0)
	{
		tmpSize -= stepSize;
		stepSize += 6;
		cntLayers++;
	}
	// std::cout << "Количество слоев: " << cntLayers << std::endl;

	const int MAX_VISIBLITY = (cntLayers < 5 ) ? cntLayers : 5;

	// const int N = COUNT_PLATFORM_LAYERS-1;

	// for (int q = -N; q <= N; q++) {
	// 	for (int r = -N; r <= N; r++) {
	// 		for (int s = -N; s <= N; s++) {
	// 			if (q + r + s == 0) {
	// 				platforms.push_back(Platform(q, r, s, PlatformState::FREE));
	// 			}
	// 		}
	// 	}
	// }

	std::map<std::string, Func> namespaces = 
	{
		{"main", Func()}, 
		{"tmp", Func()}
	};

	std::string command;
	std::vector<Variable> variables;
	variables.push_back(Variable(varTypes::digit, "robotMoving", {1}, {0}));
	variables.push_back(Variable(varTypes::digit, "robotRotate", {1}, {0}));

	Expression expr;

	std::cout << ">>> ";
	while (std::getline(std::cin, command))
	{
		// std::cout << "Вы ввели: " << command << std::endl;
		if (command == "exit" || command == "q")
		{
			break;
		}

		std::vector<std::string> subcommands = split(command);

		// for (auto &subcommands[commInd] : subcommands)
		for (int commInd=0; commInd < subcommands.size(); commInd++)
		{
			mind--;

			if (mind == 0)
			{
				std::cout << "Робот сошел с ума от недостатка вежливости" << std::endl;
				exit(1);
			}
			// std::string subcommands[commInd] = command.substr(0, pos);
			// std::cout << "подкоманда: " << subcommands[commInd] << std::endl;
			if (!subcommands[commInd].empty())
			{
				if (subcommands[commInd].find("thank you") != std::string::npos)
				{
					mind+=2;
					if (mind > 10)
					{
						std::cout << "Робот сошел с ума от излишней вежливости" << std::endl;
						exit(1);
					}
				}
				else if (subcommands[commInd].find("please") != std::string::npos)
				{
					mind+=2;
					if (mind > 10)
					{
						std::cout << "Робот сошел с ума от излишней вежливости" << std::endl;
						exit(1);
					}
				}
				else if (subcommands[commInd].find("surroundings") != std::string::npos)
				{
					std::string strVarname = extractBetweenWords(subcommands[commInd], "(", ")");
					strVarname=strVarname+"=";
					
					for (auto oDir : directions)
					{
						int lineCheck = 1;

						std::vector<int> robotPos = robot.getPos();
						std::vector<int> checkPlatform = robotPos;
						bool canCheck = true;
						while ((lineCheck < MAX_VISIBLITY) && canCheck)
						{
							checkPlatform[0] += oDir.getPos()[0];
							checkPlatform[1] += oDir.getPos()[1];
							checkPlatform[2] += oDir.getPos()[2];
							for (int i=0; i < platforms.size();i++)
							{
								std::vector<int> platformPos = platforms[i].getPos();
								if (platformPos[0] == checkPlatform[0] && platformPos[1] == checkPlatform[1] && platformPos[2] == checkPlatform[2])
								{
									if (platforms[i].getState() == PlatformState::FREE)
									{
										// можно дальше смотреть
									}
									if (platforms[i].getState() == PlatformState::WALL)
									{
										std::cout << "[" << platformPos[0] << "," << platformPos[1] << "," << platformPos[2] << "]" << " стена" << std::endl;
										canCheck = false;
										break;
									}
									if (platforms[i].getState() == PlatformState::EXIT)
									{
										std::cout << "[" << platformPos[0] << "," << platformPos[1] << "," << platformPos[2] << "]" << " выход" << std::endl;
										mind=10;
										canCheck = false; 
										break;
									}
								}
							}
							lineCheck++;
						}
					}

				}
				else if (subcommands[commInd].find("rotate") != std::string::npos)
				{
					std::string strRotate = extractBetweenWords(subcommands[commInd], "(", ")");
					strRotate="robotRotate="+strRotate;
					int res;
					if (expr.isExpression(strRotate))
					{
						expr.evaluate(strRotate, variables, res);
					}
					if (res % 60 == 0)
					{
						res /= 60;
						std::cout << "Поворот РОБОТА на " << res << std::endl;
						int curDir = robot.getDir();
						std::cout << "Текущий поворот робота: " << curDir*60 << std::endl;
						curDir += res;
						robot.setDir(curDir);
						std::cout << "Новый поворот робота: " << robot.getDir()*60 << std::endl;
					}
					

				}
				else if (subcommands[commInd].find("move") != std::string::npos)
				{
					std::string strMove = extractBetweenWords(subcommands[commInd], "(", ")");
					strMove="robotMoving="+strMove;
					int res;
					if (expr.isExpression(strMove))
					{
						expr.evaluate(strMove, variables, res);
					}
					std::cout << "ДВИЖЕНИЕ РОБОТА на" << res << std::endl;
					std::vector<int> curPos = robot.getPos();
					std::cout << "Текущая позиция робота: " << curPos[0] << " " << curPos[1] << " " << curPos[2] << std::endl;
					std::vector<int> moveOn = directions[robot.getDir()].getPos();
					for (int i = 0; i < res; i++)
					{
					curPos[0] += moveOn[0];
					curPos[1] += moveOn[1];
					curPos[2] += moveOn[2];
					robot.setPos(curPos);
					std::cout << "Новая позиция робота: " << curPos[0] << " " << curPos[1] << " " << curPos[2] << std::endl;
					
						for (int i=0; i < platforms.size();i++)
						{
							std::vector<int> platformPos = platforms[i].getPos();
							if (platformPos[0] == curPos[0] && platformPos[1] == curPos[1] && platformPos[2] == curPos[2])
							{
								if (platforms[i].getState() == PlatformState::FREE)
								{
									// все норм
								}
								if (platforms[i].getState() == PlatformState::WALL)
								{
									std::cout << "Робот считает, что его хотят убить, он обиделся." << std::endl;
									exit(1);
								}
								if (platforms[i].getState() == PlatformState::EXIT)
								{
									std::cout << "Робот вышел из лабиринта." << std::endl;
									exit(0);
								}
							}
						}
					}
				}
				else if (subcommands[commInd].find("routing") != std::string::npos)
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
					if (subcommands[commInd].find("otherwise") != std::string::npos)
					{
						std::string tmp = extractFromWord(subcommands[commInd], "otherwise {");
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
					// interpretCommand(subcommands[commInd], robot, maze); DELETE ME
				}
			}
		}

		std::cout << ">>> ";
	}

	return 0;
}

