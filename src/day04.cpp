#include "allDays.h"
#include "helpers.h"
#include <set>
#include <map>
#include <tuple>
#include <array>

bool isAnagram(const std::string &word, const std::string &word2)
{
    std::array<int, 256> buff{};
    for(auto&& l: word){
        buff[l]++;
    }
    for(auto&& l: word2){
        buff[l]--;
    }
    for(auto&& l: buff){
        if(l != 0) return false;
    }
    return true;
}

bool chceckValid(const std::string &line, bool security_lvl2)
{
    std::set<std::string> line_set;
    bool succeeds;
    auto line_vec = Calendar::Helpers::parse_line_string(line, isspace);
    for (auto &&part : line_vec)
    {
        std::tie(std::ignore, succeeds) = line_set.insert(part);
        if (!succeeds)
            return false;
    }
    if(security_lvl2)
        for (auto it = line_vec.begin(); it != line_vec.end(); it++)
        {
            for (auto jt = line_vec.begin(); jt != line_vec.end(); jt++)
            {
                if(it == jt) continue;
                if(isAnagram(*it, *jt)) return false;
            }
        }
    return true;
}

void Calendar::Day04::run(const int part)
{
    assert(part == 1 || part == 2);

    std::ifstream ifs("../inputs/day04_input.dat");
    int result = 0;
    for (std::string line; std::getline(ifs, line);)
    {
        if (chceckValid(line, part == 2 ? true : false))
            result++;
    }
    
    std::cout << "Day 04 - result of part " << part << " : " << result << std::endl;

    ifs.close();
}