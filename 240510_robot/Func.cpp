#include "Func.h"

Func::Func(const std::string& funcType, const std::string& funcName, const std::vector<std::string>& params, const std::vector<std::string>& funcBody)
        : type(funcType), name(funcName), parameters(params), body(funcBody) {}



void Func::call(const std::vector<std::string>& args) const
{
    std::cout << "Calling function " << name << " with arguments: ";
    for (const auto& arg : args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;
    std::cout << "Function body execution:" << std::endl;
    for (const auto& line : body) {
        std::cout << line << std::endl;
    }
}