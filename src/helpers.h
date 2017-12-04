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
template <typename DelimeterFunc>
std::vector<std::string> parse_line_string(const std::string &line, DelimeterFunc &&isDelimeter)
{
    std::vector<char> buff;
    std::vector<std::string> toReturn;
    for (auto it = line.begin(); it != line.end(); it++)
    {
        if (isDelimeter(*it))
        {
            const std::string number(buff.begin(), buff.end());
            toReturn.push_back(number);
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
        toReturn.push_back(number);
        buff.clear();
    }
    return toReturn;
}
}
}
