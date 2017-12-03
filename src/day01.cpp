#include "allDays.h"

void Calendar::Day01::run(const int part)
{
    assert(part == 1 || part == 2);
    std::vector<int> numbers;
    std::ifstream ifs("../inputs/input_test.dat");

    char c;
    while (ifs.get(c))
    {
        numbers.push_back(c - '0'); 
    }
    int sum = 0;
    int sum1 = 0.0;
    int *last1 = nullptr;
    last1 = new int (9);    
    if (part == 1)
    {
        for (int i = 1; i < numbers.size(); i++)
        {
            if (numbers[i] == *last1)
            {
                sum += *last1;
                *last1 = numbers[i];
            }
        }
        //check last and first
        // if(numbers.back() == numbers.front()){
        //     sum += numbers.back();
        // }
    }
    else
    {
        const int step_forward = numbers.size() / 2;
        for (int i = 0; i < numbers.size(); i++)
        {
            if (numbers[i] == numbers[(i + step_forward) % numbers.size()])
            {
                sum += numbers[i];
            }
        }
    }
    std::cout << "Day 01 - result of part "<< part << " : " << sum << std::endl;
    ifs.close();
}