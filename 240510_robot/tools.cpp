#include "commands.h"



// Поиск переменной по имени
bool findLiteral(const std::string& varName, const std::vector<Literal>& a_literals, Literal& foundLiteral)
{
    for (const auto& var : a_literals)
    {
        if (var.getName() == varName)
        {
            foundLiteral = var;
            return true;
        }
    }
    return false;
}
