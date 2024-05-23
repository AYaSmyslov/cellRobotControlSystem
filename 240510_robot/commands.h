#pragma once

#include <string>
#include <regex>
#include "Variable.h"
#include "Expression.h"
#include "Parser.h"

// tools.cpp - НЕ КОМАНДЫ, эти функции используются командами ниже
bool findVariable(const std::string &varName, const std::vector<Variable> &a_literals, Variable &foundVariable);

// declare.cpp
Variable parseVariableDeclaration(const std::string &a_declaration); // Объявление переменной

std::string getSize(const std::string &a_cmd, const std::vector<Variable> &a_literals); // Узнать размерность

std::string resize(const std::string &a_cmd, std::vector<Variable> &a_variables); // Изменить размерность

// TODO: ПЕРЕНЕСТИ В Expression
template <typename Predicate>
bool check_majority(const std::vector<int>& data, Predicate pred);

int cmpZero(const std::string &a_op, const std::vector<int>& a_data); // TODO: ПЕРЕНЕСТИ В Expression

std::vector<int> parseNumbers(const std::string& input); // TODO: ПЕРЕНЕСТИ В Expression
bool most(const std::vector<int>& numbers); // TODO: ПЕРЕНЕСТИ В Expression

// print.cpp
int getArrayElement(const std::vector<int> &indices, Variable &literal);

std::string printFormatted(const std::vector<int> &a_sizes, std::vector<int> &a_values, int a_depth); // Форматирование значения переменной

std::string printVar(const std::string &a_cmd, const std::vector<Variable> &a_literals); // Вывести значение переменной
