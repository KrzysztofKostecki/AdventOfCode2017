#include "allDays.h"
#include "helpers.h"
#include <set>
#include <map>
#include <tuple>
#include <array>

void Calendar::Day06::run(const int part)
{
    assert(part == 1 || part == 2);

    std::ifstream ifs("../inputs/day06_input.dat");
    int result_one = 0, result_two = 0;
    std::vector<int> data;
    auto delim = [](char c) -> bool{return c == '\t';};
    for (std::string line; std::getline(ifs, line);)
    {
        data = Calendar::Helpers::parse_line<int>(line, delim);
    }
    std::set<std::vector<int>> history;
    
    std::vector<int> was_seen;
    bool second_run = false;
    history.insert({data.begin(), data.end()});
    while(true){
        auto max_it = std::max_element(data.begin(), data.end());
        size_t begin_index = max_it-data.begin() + 1;
        size_t end_index = begin_index + *max_it;
        *max_it = 0;
        result_one++;
        for(int i = begin_index; i < end_index; i++){
            data[(i) % data.size()]++;
        }

        if(second_run){
            result_two++;
            if(was_seen == data)
                break;
        }else{
            auto result = history.insert({data.begin(), data.end()});

            if(!result.second) {
                was_seen = *result.first;
                second_run = true;
                if(part == 1) break;
                continue;
            }
        }
    }
    
    std::cout << "Day 06 - result of part " << part << " : " << ((part == 1) ? result_one : result_two) << std::endl;

    ifs.close();
}