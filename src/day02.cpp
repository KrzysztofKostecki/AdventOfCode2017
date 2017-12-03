#include "allDays.h"
#include "helpers.h"

int get_checksum_1(const std::string &line)
{
    auto numbers_in_line = Calendar::Helpers::parse_line<int>(line, isspace);
    int min = *std::min_element(numbers_in_line.begin(), numbers_in_line.end());
    int max = *std::max_element(numbers_in_line.begin(), numbers_in_line.end());
    return max - min;
}

int get_checksum_2(const std::string &line)
{
    auto numbers_in_line = Calendar::Helpers::parse_line<int>(line, isspace);
    for (auto &&i : numbers_in_line)
    {
        for (auto j : numbers_in_line)
        {
            if (i % j == 0 && i != j)
                return i / j;
        }
    }
    return 0;
}

void Calendar::Day02::run(const int part)
{
    assert(part == 1 || part == 2);

    std::ifstream ifs("../inputs/day02_input.dat");

    int checksum = 0;
    for (std::string line; std::getline(ifs, line);)
    {
        if (part == 1)
            checksum += get_checksum_1(line);
        else
            checksum += get_checksum_2(line);
    }

    std::cout << "Day 02 - result of part " << part << " : " << checksum << std::endl;

    ifs.close();
}