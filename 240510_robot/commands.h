#pragma once

#include <string>
#include <regex>
#include "Literal.h"

// tools.cpp - НЕ КОМАНДЫ, эти функции используются командами ниже
bool findLiteral(const std::string& varName, const std::vector<Literal>& a_literals, Literal& foundLiteral);

// declare.cpp
Literal parseLiteralDeclaration(const std::string &a_declaration); // Объявление переменной

std::string getSize(const std::string &a_cmd, const std::vector<Literal> &a_literals); // Узнать размерность

// print.cpp
int getArrayElement(const std::vector<int> &indices, Literal &literal);

std::string printFormatted(const std::vector<int>& a_sizes, std::vector<int>& a_values, int a_depth); // Форматирование значения переменной

std::string printVar(const std::string &a_cmd, const std::vector<Literal> &a_literals); // Вывести значение переменной
