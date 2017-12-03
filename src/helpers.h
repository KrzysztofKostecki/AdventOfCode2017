#pragma once

#include "standard_includes.h"

namespace Calendar
{
namespace Helpers
{
template <typename NumericType, typename DelimeterFunc>
std::vector<NumericType> parse_line(const std::string &line, DelimeterFunc &&isDelimeter)
{
    std::vector<char> buff;
    std::vector<NumericType> toReturn;
    for (auto it = line.begin(); it != line.end(); it++)
    {
        if (isDelimeter(*it))
        {
            const std::string number(buff.begin(), buff.end());
            toReturn.push_back(std::stoi(number));
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
        toReturn.push_back(std::stoi(number));
        buff.clear();
    }
    return toReturn;
}
}
}
