#pragma once

#include <string>
#include <regex>
#include "Variable.h"

// tools.cpp - НЕ КОМАНДЫ, эти функции используются командами ниже
bool findVariable(const std::string& varName, const std::vector<Variable>& a_variables, Variable& foundVariable);

// declare.cpp
Variable parseVariableDeclaration(const std::string &a_declaration); // Объявление переменной

std::string getSize(const std::string &a_cmd, const std::vector<Variable> &a_variables); // Узнать размерность

// print.cpp
int getArrayElement(const std::vector<int> &indices, Variable &variable);

std::string printFormatted(const std::vector<int>& a_sizes, std::vector<int>& a_values, int a_depth); // Форматирование значения переменной

std::string printVar(const std::string &a_cmd, const std::vector<Variable> &a_variables); // Вывести значение переменной
