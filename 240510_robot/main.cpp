#include <stdio.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Literal.h"
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
    for (int i = 1 ; i < argc ; ++i)
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
    std::vector<Literal> literals;

    std::cout << ">>> ";
    while (std::getline(std::cin, command))
    {
        std::cout << "Вы ввели: " << command << std::endl;
        if (command == "exit" || command == "q")
        {
            break;
        }
        if (command.find("digit") != std::string::npos || command.find("logic") != std::string::npos)
        {
            literals.push_back(parseLiteralDeclaration(command));
            literals.back().print();
        } 
        else if (command.find("size") != std::string::npos)
        {
            std::cout << getSize(command, literals);
        }
        else if (command.find("print") != std::string::npos)
        {
            std::cout << printVar(command, literals);
        }
        else
        {
            interpretCommand(command, robot, maze);
        }
        std::cout << ">>> ";
    }

    return 0;
}