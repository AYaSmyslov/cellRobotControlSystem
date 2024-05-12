#include "Variable.h"

Variable::Variable()
{
}



Variable::Variable(
    const varTypes &a_varType,
    const std::string &a_name,
    const std::vector<int> &a_dim,
    const std::vector<int> &a_defVal)
    : _varType(a_varType), _name(a_name), _dimensions(a_dim), _value(a_defVal) {}



Variable::Variable(
    const std::string &a_varType,
    const std::string &a_name,
    const std::string &a_dim,
    const std::string &a_defVal)
{
    if (_convertStrToType(a_varType) == -1)
    {
        std::cout << "Ошибка определения типа переменной" << std::endl;
    }
    _name = a_name;
    _name.erase(std::remove(_name.begin(), _name.end(), ' '), _name.end());
    if (_convertStrToDim(a_dim) == -1)
    {
        std::cout << "Ошибка определения размерности переменной" << std::endl;
    };
    if (_convertStrToDefVal(a_defVal))
    {
        std::cout << "Ошибка значения переменной" << std::endl;
    };
}



Variable::~Variable()
{
}



// Variable &Variable::operator=(const Variable &other)
// {
//     if (this != &other)
//     {
//         // data = other.data;
//         if (_varType == other.getType())
//         {
//             _name = other.getName();
//             _dimensions = other.getDim();
//             _value = other.getValue();
//         }
//         else
//         {
//             throw std::runtime_error("Fields do not match");
//         }
//     }
//     return *this;
// }

// bool Variable::operator==(const Variable &other) const
// {
//     return (this->getName() == other.getName());
// }



// Парсинг типа переменной
int Variable::_convertStrToType(const std::string &a_varType)
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
int Variable::_convertStrToDim(const std::string &a_dim)
{
    std::stringstream ss(a_dim);
    char c;
    int num;
    while (ss >> c)
    {
        if (isdigit(c))
        {
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
int Variable::_convertStrToDefVal(const std::string &a_defVal)
{
    int size = 1;
    for (auto i : _dimensions)
    {
        size *= i;
    }

    _value.resize(size);
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
        std::fill(_value.begin(), _value.end(), stoi(a_defVal, nullptr, base));
        return 0;
    }
    if (_varType == varTypes::logic)
    {

        if (a_defVal == "true")
        {
            std::fill(_value.begin(), _value.end(), 1);
            return 0;
        }
        else if (a_defVal == "false")
        {
            std::fill(_value.begin(), _value.end(), 0);
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
    for (int dim : _dimensions)
    {
        std::cout << dim << " ";
    }
    std::cout << std::endl;
    std::cout << "Default value: ";
    for (int val : _value)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Type: " << (_varType == 1 ? "logic" : "digit") << std::endl;
}



std::vector<int> Variable::size() const
{
    return _dimensions;
}



// по-тупому сделано
void Variable::resize(const std::vector<int> &a_sizes)
{
    int oldSize = 1, newSize = 1;
    for (int dim : _dimensions) oldSize *= dim;
    for (int dim : a_sizes) newSize *= dim; 
     _value.resize(newSize);

    if (newSize > oldSize)
    {
        if (_varType == varTypes::digit)
        {
            std::fill(_value.begin() + oldSize, _value.end(), 0);
        }
        if (_varType == varTypes::logic)
        {
            std::fill(_value.begin() + oldSize, _value.end(), 1);
        }
        _dimensions = a_sizes;
    }
}



Variable Variable::toLogic()
{

    Variable tmp(varTypes::logic, _name, _dimensions, _value);
    return tmp;
}



Variable Variable::toDigit()
{
    std::vector<int> newValue;
    for (const auto &i : _value)
    {
        newValue.push_back((i == 0 ? 0 : 1));
    }
    Variable tmp(varTypes::digit, _name, _dimensions, newValue);
    return tmp;
}



varTypes Variable::getType() const
{
    return _varType;
}



std::string Variable::getName() const
{
    return _name;
}



std::vector<int> Variable::getDim() const
{
    return _dimensions;
}



std::vector<int> Variable::getValue() const
{
    return _value;
}