#include "allDays.h"
#include "helpers.h"
#include <unordered_map>
#include <cmath>
#include <tuple>
#include <list>
#include <array>
#include <map>

#define pos(x, y) std::make_pair(x, y)
using Position = std::pair<int, int>;

struct Circle
{
    std::list<Position> positions;
    int _size;
    Circle(int size, const Position &starting_position)
    {
        generate(size, starting_position);
    }
    void generate(int size, const Position &starting_position)
    {
        _size = size;
        positions.clear();
        positions.push_back(starting_position);
        int x = starting_position.first;
        int y = starting_position.second;
        int end = size * 8;
        while (positions.size() < end)
        {
            //up
            while (possible(x, y + 1))
            {
                auto toAdd = pos(x, ++y);
                positions.push_back(toAdd);
            }
            //left
            while (possible(x - 1, y))
            {
                auto toAdd = pos(--x, y);
                positions.push_back(toAdd);
            }
            //down
            while (possible(x, y - 1))
            {
                auto toAdd = pos(x, --y);
                positions.push_back(toAdd);
            }
            //right
            while (possible(x + 1, y))
            {
                auto toAdd = pos(++x, y);
                positions.push_back(toAdd);
            }
        }
    }
    bool possible(int x, int y)
    {
        if (x < (-_size) || x > _size)
            return false;
        if (y < (-_size) || y > _size)
            return false;
        return true;
    }
    std::pair<Position, bool> get_next_position()
    {
        if (positions.empty())
            return std::make_pair(pos(0, 0), false);
        auto toReturn = std::make_pair(positions.front(), true);
        positions.pop_front();
        return toReturn;
    }
};

class Grid
{
    std::unordered_map<int, Position> square_position;
    Circle c;
    int curr_circle_size;

  public:
    int size;

    Grid(int max_value) : size(max_value),
                          c(1, pos(1, 0)),
                          curr_circle_size(1)
    {
        //first position need to be initialised separately
        square_position.insert(std::make_pair(1, pos(0, 0)));
        for (int i = 2; i <= max_value; i++)
        {
            square_position.insert(std::make_pair(i, generate_next_position(i)));
        }
    }
    int taxicab_distance(const int pos1, const int pos2)
    {
        int x1 = square_position.at(pos1).first;
        int y1 = square_position.at(pos1).second;
        int x2 = square_position.at(pos2).first;
        int y2 = square_position.at(pos2).second;
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    friend std::ostream &operator<<(std::ostream &os, const Grid &grid)
    {
        for (const auto &it : grid.square_position)
        {
            os << it.second.first << "\t" << it.second.second << "\t" << it.first << std::endl;
        }
        return os;
    }

  private:
    //temp values
    int x, y;
    //function generates next position
    //it stores the information about last and where to move next
    Position generate_next_position(const int i)
    {
        Position p;
        bool has_next;
        std::tie(p, has_next) = c.get_next_position();

        if (!has_next)
        {
            c.generate(++curr_circle_size, pos(x + 1, y));
            std::tie(p, has_next) = c.get_next_position();
        }

        x = p.first;
        y = p.second;
        return pos(x, y);
    }
    //gives back part of the circle wee need to move forawrd in this lap
};

class Grid2
{
    std::map<Position, int> square_position;
    Circle c;
    int curr_circle_size;
    const int puzzle_input;
    int solution_value;

  public:
    Grid2(const int _puzzle_input) : c(1, pos(1, 0)),
                                     curr_circle_size(1),
                                     puzzle_input(_puzzle_input)
    {
        //first position need to be initialised separately
        Position last_position = pos(0, 0);
        square_position.insert(std::make_pair(last_position, 1));
        for (int i = 1;;i++)
        {
            auto next_position = generate_next_position(i);
            int square_value = adjacents_values(next_position);
            if (square_value > puzzle_input)
            {
                solution_value = square_value;
                break;
            }
            square_position.insert(std::make_pair(next_position, square_value));
        }
    }
    int get_solution() const{
        return this->solution_value;
    }
    friend std::ostream &operator<<(std::ostream &os, const Grid2 &grid)
    {
        for (const auto &it : grid.square_position)
        {
            os << it.first.first << "\t" << it.first.second << "\t" << it.second << std::endl;
        }
        return os;
    }

  private:
    //temp values
    int x, y;
    //function generates next position
    //it stores the information about last and where to move next
    Position generate_next_position(const int i)
    {
        Position p;
        bool has_next;
        std::tie(p, has_next) = c.get_next_position();

        if (!has_next)
        {
            c.generate(++curr_circle_size, pos(x + 1, y));
            std::tie(p, has_next) = c.get_next_position();
        }

        x = p.first;
        y = p.second;
        return pos(x, y);
    }

    std::array<Position, 8> get_adjacents(const Position &pos)
    {
        int x = pos.first, y = pos.second;
        return {{pos(x + 1, y),
                 pos(x + 1, y + 1),
                 pos(x, y + 1),
                 pos(x - 1, y + 1),
                 pos(x - 1, y),
                 pos(x - 1, y - 1),
                 pos(x, y - 1),
                 pos(x + 1, y - 1)}};
    }

    int adjacents_values(const Position &pos)
    {
        int toReturn = 0;
        for (auto &&p : get_adjacents(pos))
        {
            try
            {
                toReturn += square_position.at(p);
            }
            catch (std::out_of_range &e)
            {
            }
        }
        return toReturn;
    }
};

void Calendar::Day03::run(const int part)
{
    assert(part == 1 || part == 2);

    std::ifstream ifs("../inputs/day03_input.dat");
    int puzzle_input;
    ifs >> puzzle_input;
    int result = 0;
    if (part == 1)
    {
        Grid grid(puzzle_input);
        result = grid.taxicab_distance(1, puzzle_input);
    }
    else
    {
        Grid2 grid2(puzzle_input);
        result = grid2.get_solution();
    }

    std::cout << "Day 03 - result of part " << part << " : " << result << std::endl;

    ifs.close();
}