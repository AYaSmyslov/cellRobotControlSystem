#include "commands.h"

/*
digit varName[[i,j,..., n]]=0|1|2|3|...|N;
logic varName[[i,j,..., n]]=true|false;
*/
Variable parseVariableDeclaration(const std::string &a_declaration)
{
	std::regex r("(digit|logic)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*(\\[[0-9]+(\\s*,\\s*[0-9]+)*\\])?\\s*=\\s*(.*)");

	std::smatch match;

	std::string varType, name, dimensions, defaultValue;

	if (std::regex_search(a_declaration, match, r) && match.size() > 1)
	{
		varType = match.str(1);
		name = match.str(2);
		dimensions = match.str(3);
		defaultValue = match.str(5);
	}
	if (dimensions.empty())
	{
		dimensions = "[1]";
	}
	Variable var(varType, name, dimensions, defaultValue);
	return var;
}



// Получить размерность переменной
// size(varName);
// #TODO:
/// ОБРАЩЕНИЯ ПО ИНДЕКСУ НЕТ!!!
std::string getSize(const std::string &a_cmd, const std::vector<Variable> &a_variables)
{
	std::regex sizeRegex("size\\(([a-zA-Z_][a-zA-Z0-9_]*)\\)");
	std::ostringstream oss;

	std::smatch match;
	if (std::regex_match(a_cmd, match, sizeRegex))
	{
		if (match.size() == 2)
		{
			std::string varName = match[1].str();
			Variable var;

			if (findVariable(varName, a_variables, var))
			{
				oss << "Найдена переменная: " << varName << std::endl;
				std::vector<int> size = var.size();
				oss << '[';

				for (int i = 0; i < size.size(); i++)
				{
					oss << size[i];
					if (i < size.size() - 1)
					{
						oss << ", ";
					}
				}
				oss << ']' << std::endl;

				return oss.str();
			}

			oss << "Переменная с именем " << varName << " не определена." << std::endl;
		}
	}
	else
	{
		oss << "Команда не соответствует формату size(varName);" << std::endl;
	}
	return oss.str();
}



// Изменить размерность переменной
/*
 resize(varName, N);
 resize(varName, [N]);
 resize(varName, [i,..,N]);
 #TODO: масштабируется по-топорному линейно, без должного учета размерности
 Пример:
 [1,2,3,4] - размерность [2,2] =>
 [[1,2],[3,4]] - с учетом размерности выглядит так
 при масштабировании до [3,3] должно быть
 [[1,2,0],[3,4,0],[0,0,0]]
 фактически выходит так:
 [[1,2,3],[4,0,0],[0,0,0]]
*/
std::string resize(const std::string &a_cmd, std::vector<Variable> &a_variables)
{
	std::regex sizeRegex("resize\\(([a-zA-Z_][a-zA-Z0-9_]*)(?:,\\s*(\\d+|\\[\\s*(?:\\d+\\s*,\\s*)*\\d+\\s*\\]))?\\)");

	std::ostringstream oss;

	std::smatch match;
	if (std::regex_match(a_cmd, match, sizeRegex))
	{
		if (match.size() >= 2)
		{
			std::string strSizes=match[2];
			if (!strSizes.empty() && strSizes.front() == '[' && strSizes.back() == ']')
			{
				strSizes.erase(0, 1);
				strSizes.pop_back();
			}
			std::stringstream indSs(strSizes);
			std::vector<int> sizes;
			int ind;
			while (indSs >> ind)
			{
				sizes.push_back(ind);
				if (indSs.peek() == ',' || indSs.peek() == ' ')
				{
					indSs.ignore();
				}
			}

			std::string varName = match[1].str();
			Variable var;

			if (findVariable(varName, a_variables, var))
			{
				oss << "Найдена переменная: " << varName << std::endl;
				auto it = std::find_if(a_variables.begin(), a_variables.end(), [&](const Variable &var)
												   {
													   return var.getName() == var.getName();
												   });
				if (it != a_variables.end())
				{
					int ind = std::distance(a_variables.begin(), it);
					a_variables[ind].resize(sizes);
				}

				oss << "Размер переменной изменен" << std::endl;				

				return oss.str();
			}

			oss << "Переменная с именем " << varName << " не определена." << std::endl;
		}
	}
	else
	{
		oss << "Команда не соответствует формату resize(varName, [i, ..., n])" << std::endl;
	}
	return oss.str();
}







