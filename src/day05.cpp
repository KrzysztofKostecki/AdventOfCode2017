#include "allDays.h"
#include "helpers.h"
#include <set>
#include <map>
#include <tuple>
#include <array>



void Calendar::Day05::run(const int part)
{
    assert(part == 1 || part == 2);

    std::ifstream ifs("../inputs/day05_input.dat");
    int result = 0;
    std::vector<int> data;
    for (std::string line; std::getline(ifs, line);)
    {
        data.push_back(std::stoi(line));
    }

    int i = 0;
    while(true){
        try{
            int& last_it = data.at(i);
            i += last_it;
            if(part == 2 && last_it >= 3)
                last_it--;
            else
                last_it++;
            result++;
        }catch(std::out_of_range& e){
            break;
        }
    }

    
    std::cout << "Day 05 - result of part " << part << " : " << result << std::endl;

    ifs.close();
}