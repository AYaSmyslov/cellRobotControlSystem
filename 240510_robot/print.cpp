#include "commands.h"



int getArrayElement(const std::vector<int> &indices, Variable &variable)
{
    const auto &dimensions = variable.getDim();

    if (dimensions.size() < indices.size())
    {
        return -1;
    }

    std::vector<int> newDim;
    if (dimensions.size() > indices.size())
    {
        // 2 2 2
        // 1 1
        // 2

        // 2 2
        // 1 1
        // 2
        int diff =  dimensions.size() -(dimensions.size() - indices.size());
        newDim.assign(dimensions.begin() + diff, dimensions.end());
        // newDim = {dimensions.back() - (dimensions.back() - indices.back())};

    }
    else
    {
        newDim = {1};
    }
    std::vector<int> newValue = variable.getValue();
    int k = 0;
    for (const auto &i : indices)
    {
        int len = newValue.size();
        int subLen = len / dimensions[k];
        int indBegin = i*subLen;
        int indEnd = indBegin + subLen-1;
        newValue.erase(newValue.begin(), newValue.begin() + indBegin);
        newValue.erase(newValue.begin() + (indEnd - indBegin + 1), newValue.end());
        k++;
    }
    Variable var(variable.getType(), variable.getName(), newDim, newValue);
    variable = var;

    return 0;
}



std::string printFormatted(const std::vector<int> &a_sizes, std::vector<int> &a_values, int a_depth = 0)
{
    std::ostringstream oss;
    if (a_sizes.size() > 1 || (a_sizes.size() == 1 && a_sizes[0] != 1))
    {
        oss << "[";
    }
    for (int i = 0; i < a_sizes[a_depth]; ++i)
    {
        if (a_depth + 1 < a_sizes.size())
        {
            oss << printFormatted(a_sizes, a_values, a_depth + 1);
        }
        else
        {
            oss << a_values.back();
            a_values.pop_back();
        }
        if (i != a_sizes[a_depth] - 1)
        {
            oss << ", ";
        }
    }
    if (a_sizes.size() > 1 || (a_sizes.size() == 1 && a_sizes[0] != 1))
    {
        oss << "]";
    }
    if (a_depth == 0)
    {
        oss << std::endl;
    }
    return oss.str();
}

// Вывести значения переменных
std::string printVar(const std::string &a_cmd, const std::vector<Variable> &a_variables)
{
    // std::regex printRegex("print\\(([a-zA-Z_][a-zA-Z0-9_]*)\\);");
    // std::regex printRegex("print\\(([a-zA-Z_][a-zA-Z0-9_]*)(\\[(\\d+(?:,\\s*\\d+)*)\\])?\\);");
    std::regex printRegex("print\\(([a-zA-Z_][a-zA-Z0-9_]*)(\\[([0-9]+(\\s*,\\s*[0-9]+)*)\\])?\\);");
    std::ostringstream oss;

    std::smatch match;
    std::vector<int> indices;
    if (std::regex_match(a_cmd, match, printRegex))
    {

        if (match.size() >= 2)
        {
            if (match.size() >= 3)
            {
                std::stringstream indSs(match[3]);
                int ind;
                while (indSs >> ind)
                {
                    indices.push_back(ind-1);
                    if (indSs.peek() == ',' || indSs.peek() == ' ')
                    {
                        indSs.ignore();
                    }
                }
            }
            std::string varName = match[1].str();
            Variable var;

            if (findVariable(varName, a_variables, var))
            {
                oss << "Значения переменной " << varName << ":" << std::endl;
                if (match.size() >= 3)
                {
                    if (getArrayElement(indices, var) == -1)
                    {
                        oss << "Ошибка индекса" << std::endl;
                        return oss.str();
                    }
                }
                const auto &size = var.size();
                std::vector<int> value = var.getValue();
                std::reverse(value.begin(), value.end());

                if (var.getType() == varTypes::digit)
                {
                    oss << printFormatted(size, value);
                }
                else if (var.getType() == varTypes::logic)
                {
                    std::string res = printFormatted(size, value);
                    size_t pos = res.find("1");
                    while (pos != std::string::npos)
                    {
                        res.replace(pos, 1, "true");
                        pos = res.find("1", pos + 1);
                    }

                    pos = res.find("0");
                    while (pos != std::string::npos)
                    {
                        res.replace(pos, 1, "false");
                        pos = res.find("0", pos + 1);
                    }
                    oss << res;
                }

                return oss.str();
            }
            else
            {
                oss << "Переменная с именем " << varName << " не определена." << std::endl;
            }
        }
    }
    else
    {
        oss << "Команда не соответствует формату print(varName);" << std::endl;
    }
    return oss.str();
}