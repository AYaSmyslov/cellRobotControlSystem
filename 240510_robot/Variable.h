#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>



class Variable
{
public:
	Variable();
	Variable(
		const std::string& a_name,
		const std::vector<int>& a_dim,
		const std::vector<int>& a_defVal,
		bool a_logic
	);
	Variable(
		const std::string& a_varType,
		const std::string& a_name,
		const std::string& a_dim,
		const std::string& a_defVal
	);
	~Variable();

	void print() const;
	std::vector<int> size() const;
	std::string getName() const;


private:

	int _convertStrToType(const std::string& a_varType);
	int _convertStrToDim(const std::string& a_dim);
	int _convertStrToDefVal(const std::string& a_defVal);

	std::string _name; // Имя переменной
	std::vector<int> _dimensions; // Размерности переменной
	std::vector<int> _defaultVal; // Значение по умолчанию
	enum varTypes
	{
		digit = 0,
		logic
	};
	varTypes _varType;
};