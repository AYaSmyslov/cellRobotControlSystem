#include "commands.h"



// Поиск переменной по имени
bool findVariable(const std::string& varName, const std::vector<Variable>& a_literals, Variable& foundVariable)
{
	for (const auto& var : a_literals)
	{
		if (var.getName() == varName)
		{
			foundVariable = var;
			return true;
		}
	}
	return false;
}



std::string removeSpaces(const std::string& str)
{
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}



std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> result;
    std::string current;
    int brace_count = 0;
    
    for (size_t i = 0; i < str.size(); ++i)
	{
        char c = str[i];
        if (c == '{')
		{
            ++brace_count;
        }
		else if (c == '}')
		{
            --brace_count;
        }

        if (c == ';' && brace_count == 0)
		{
            result.push_back(current);
            current.clear();
        }
		else
		{
            current += c;
        }
    }
    if (!current.empty())
	{
        result.push_back(current);
    }

    return result;
}



std::string extractBetweenWords(const std::string& str, const std::string& word1, const std::string& word2) 
{
    auto pos1 = str.find(word1);
    auto pos2 = str.find(word2);
    if (pos1 != std::string::npos && pos2 != std::string::npos && pos2 > pos1)
	{
        return str.substr(pos1 + word1.length(), pos2 - pos1 - word1.length());
    }
    return "";
}


std::string extractFromWord(const std::string& str, const std::string& word)
{
    auto pos = str.find(word);
    if (pos != std::string::npos)
	{
        return str.substr(pos + word.length());
    }
    return "";
}



std::string extractToWord(const std::string& str, const std::string& word)
{
    auto pos = str.find(word);
    if (pos != std::string::npos)
	{
        return str.substr(0, pos);
    }
    return "";
}



std::vector<int> strToVector(std::string a_str)
{
	std::vector<int> res;
	a_str.erase(std::remove(a_str.begin(), a_str.end(), '['), a_str.end());
	a_str.erase(std::remove(a_str.begin(), a_str.end(), ']'), a_str.end());
	a_str.erase(std::remove(a_str.begin(), a_str.end(), ' '), a_str.end());

	// Разбиваем строку на отдельные числа
	std::istringstream ss(a_str);
	std::string token;
	while (std::getline(ss, token, ',')) {
		res.push_back(std::stoi(token));
	}
	return res;
}