#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

class Func
{
public:
    std::string type;
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::string> body;

    Func(const std::string& funcType, const std::string& funcName, const std::vector<std::string>& params, const std::vector<std::string>& funcBody);

    void call(const std::vector<std::string>& args) const;
};