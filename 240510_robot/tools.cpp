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
