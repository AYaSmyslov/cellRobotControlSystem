#include "commands.h"



// Поиск переменной по имени
bool findVariable(const std::string& varName, const std::vector<Variable>& a_variables, Variable& foundVariable)
{
    for (const auto& var : a_variables)
    {
        if (var.getName() == varName)
        {
            foundVariable = var;
            return true;
        }
    }
    return false;
}
