#include <stdio.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>

#include "Variable.h"
#include "Robot.h"

// Определение структуры лабиринта
struct Maze
{
    std::vector<std::vector<int>> grid; // сетка лабиринта
    // ... другие свойства и методы ...
};



/*
digit varName[[i,j,..., n]]=0|1|2|3|...|N;
logic varName[[i,j,..., n]]=true|false;
*/
Variable parseVariableDeclaration(const std::string &a_declaration) {
    // std::regex r("(digit|logic)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*(\\[[0-9]+(,[0-9]+)*\\])?\\s*=\\s*(.*);");
    std::regex r("(digit|logic)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*(\\[[0-9]+(\\s*,\\s*[0-9]+)*\\])?\\s*=\\s*(.*);");

    std::smatch match;
    
    std::string varType, name, dimensions, defaultValue;

    if (std::regex_search(a_declaration, match, r) && match.size() > 1) {
        varType = match.str(1);
        name = match.str(2);
        dimensions = match.str(3);
        defaultValue = match.str(5);
    }
    if (dimensions.empty()) {
        dimensions = "[1]";
    }
    Variable var(varType, name, dimensions, defaultValue);
    return var;
}



// Получить размерность переменной
void getSize(const std::string &a_cmd, const std::vector<Variable> &a_variables) {
    std::regex sizeRegex("size\\(([a-zA-Z_][a-zA-Z0-9_]*)\\);");

    std::smatch match;
    if (std::regex_match(a_cmd, match, sizeRegex))
    {
        if (match.size() == 2)
        {
            std::string varName = match[1].str();

            for (const auto& var : a_variables)
            {
                if (var.getName() == varName)
                {
                    std::cout << "Найдена переменная: " << varName << std::endl;
                    std::vector<int> size = var.size();
                    std::cout << '[';

                    for (int i=0; i<size.size(); i++)
                    {
                        std::cout << size[i];
                        if (i<size.size()-1)
                        {
                            std::cout << ", ";
                        }
                    }
                    std::cout << ']' << std::endl;

                    return;
                }
            }

            std::cout << "Переменная с именем " << varName << " не найдена." << std::endl;
        }
    } 
    else
    {
        std::cout << "Команда не соответствует формату size(varName);" << std::endl;
    }
}



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
    std::vector<Variable> variables;

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
            variables.push_back(parseVariableDeclaration(command));
            variables.back().print();
        } 
        else if (command.find("size") != std::string::npos)
        {
            getSize(command, variables);
        }
        else
        {
            interpretCommand(command, robot, maze);
        }
        std::cout << ">>> ";
    }

    return 0;
}