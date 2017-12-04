#pragma once

#include "standard_includes.h"
#include <sstream>

namespace Calendar
{
namespace Helpers
{
template <typename DataType, typename DelimeterFunc>
std::vector<DataType> parse_line(const std::string &line, DelimeterFunc &&isDelimeter)
{
    std::vector<char> buff;
    std::vector<DataType> toReturn;
    for (auto it = line.begin(); it != line.end(); it++)
    {
        if (isDelimeter(*it))
        {
            const std::string number(buff.begin(), buff.end());
            std::istringstream ss(number);
            DataType value;
            ss >> value;
            toReturn.push_back(value);
            buff.clear();
        }
        else
        {
            buff.push_back(*it);
        }
    }
    //to make sure if buff is empty
    if (!buff.empty())
    {
        const std::string number(buff.begin(), buff.end());
        std::istringstream ss(number);
        DataType value;
        ss >> value;
        toReturn.push_back(value);
        buff.clear();
    }
    return toReturn;
}
}
}
