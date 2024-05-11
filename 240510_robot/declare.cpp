#include "commands.h"

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
std::string getSize(const std::string &a_cmd, const std::vector<Variable> &a_variables)
{
    std::regex sizeRegex("size\\(([a-zA-Z_][a-zA-Z0-9_]*)\\);");
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

                for (int i=0; i<size.size(); i++)
                {
                    oss << size[i];
                    if (i<size.size()-1)
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