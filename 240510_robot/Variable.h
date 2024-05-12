#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

enum varTypes
{
	digit = 0,
	logic
};

class Variable
{
public:
	Variable();
	Variable(
		const varTypes &a_varType,
		const std::string &a_name,
		const std::vector<int> &a_dim,
		const std::vector<int> &a_defVal
	);
	Variable(
		const std::string& a_varType,
		const std::string& a_name,
		const std::string& a_dim,
		const std::string& a_defVal
	);
	~Variable();

    // Variable& operator=(const Variable& other);
	// bool operator==(const Variable& other) const;


	void print() const;
	std::vector<int> size() const;
	void resize(const std::vector<int> &a_sizes);
	Variable toLogic();
	Variable toDigit();
	varTypes getType() const;
	std::string getName() const;
	std::vector<int> getDim() const;
	std::vector<int> getValue() const;
	


private:

	int _convertStrToType(const std::string& a_varType);
	int _convertStrToDim(const std::string& a_dim);
	int _convertStrToDefVal(const std::string& a_defVal);

	varTypes _varType; // Тип
	std::string _name; // Имя
	std::vector<int> _dimensions; // Размерность
	std::vector<int> _value; // Значение
};