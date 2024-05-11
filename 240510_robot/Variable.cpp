#include "Variable.h"



Variable::Variable()
{
}



Variable::Variable(
    const std::string& a_name,
    const std::vector<int>& a_dim,
    const std::vector<int>& a_defVal,
    bool a_logic
)
    : _name(a_name), _dimensions(a_dim), _defaultVal(a_defVal) {}



Variable::Variable(
    const std::string& a_varType,
    const std::string& a_name,
    const std::string& a_dim,
    const std::string& a_defVal
)
{
    if (_convertStrToType(a_varType) == -1) { std::cout << "Ошибка определения типа переменной" << std::endl; } 
    _name = a_name;
    _name.erase(std::remove(_name.begin(), _name.end(), ' '), _name.end());
    if (_convertStrToDim(a_dim)  == -1) { std::cout << "Ошибка определения размерности переменной" << std::endl; } ;
    if (_convertStrToDefVal(a_defVal)) { std::cout << "Ошибка значения переменной" << std::endl; } ;
}



Variable::~Variable()
{
}



// Парсинг типа переменной
int Variable::_convertStrToType(const std::string& a_varType)
{
    if (a_varType == "digit")
    {
        _varType = varTypes::digit;
        return 0;
    }
    if (a_varType == "logic")
    {
        _varType = varTypes::logic;
        return 0;
    }

    return -1;
}



// Парсинг размерности переменной
int Variable::_convertStrToDim(const std::string& a_dim)
{
    std::stringstream ss(a_dim);
    char c;
    int num;
    while (ss >> c) {
        if (isdigit(c)) {
            ss.putback(c);
            ss >> num;
            if (num <= 0)
            {
                return -1;
            }
            _dimensions.push_back(num);
        }
    }
    return 0;
}



// Заполнение переменной
int Variable::_convertStrToDefVal(const std::string& a_defVal)
{
    int size = 1;
    for (auto i : _dimensions)
    {
        size *= i;
    }

    _defaultVal.resize(size);
    if (_varType == varTypes::digit)
    {
        int base = 10;
        if (a_defVal.size() > 1 && a_defVal[0] == '0')
        {
            if (a_defVal[1] == 'x' || a_defVal[1] == 'X')
            {
                base = 16;
            } 
            else 
            {
                base = 8;
            }
        }
        std::fill(_defaultVal.begin(), _defaultVal.end(), stoi(a_defVal, nullptr, base));
        return 0;

    }
    if (_varType == varTypes::logic)
    {

        if (a_defVal == "true")
        {
            std::fill(_defaultVal.begin(), _defaultVal.end(), 1);
            return 0;
        }
        else if (a_defVal == "false")
        {
            std::fill(_defaultVal.begin(), _defaultVal.end(), 0);
            return 0;

        }
    } 
    return -1;
}


// Метод для вывода информации о переменной
void Variable::print() const
{
    std::cout << "Variable name: " << _name << std::endl;
    std::cout << "Dimensions: ";
    for (int dim : _dimensions) {
        std::cout << dim << " ";
    }
    std::cout << std::endl;
    std::cout << "Default value: ";
    for (int val : _defaultVal) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Type: " << (_varType == 1 ? "logic" : "digit") << std::endl;
}



std::vector<int> Variable::size() const
{
    return _dimensions;
}

std::string Variable::getName() const
{
    return _name;
}