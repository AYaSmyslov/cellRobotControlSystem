#pragma once

#include <string>
#include <regex>
#include "Variable.h"
#include "Parser.h"

// tools.cpp - НЕ КОМАНДЫ, эти функции используются командами ниже
bool findVariable(const std::string &varName, const std::vector<Variable> &a_literals, Variable &foundVariable);

// declare.cpp
Variable parseVariableDeclaration(const std::string &a_declaration); // Объявление переменной

std::string getSize(const std::string &a_cmd, const std::vector<Variable> &a_literals); // Узнать размерность

std::string resize(const std::string &a_cmd, std::vector<Variable> &a_variables); // Изменить размерность

// print.cpp
int getArrayElement(const std::vector<int> &indices, Variable &literal);

std::string printFormatted(const std::vector<int> &a_sizes, std::vector<int> &a_values, int a_depth); // Форматирование значения переменной

std::string printVar(const std::string &a_cmd, const std::vector<Variable> &a_literals); // Вывести значение переменной
