#include <iostream>
#include <vector>
#include "knapsack.h"

int main()
{
    std::cout << "knapsack" << std::endl;

    std::cout << "dp:\n";
    std::vector<KnapsackItem> items{
        {1,2,2},
        {2,5,5},
        {3,3,3},
        {4,4,4}
    };

    size_t capacity = 7;

    auto dp = knapsackValue(items, capacity);

    for (const auto& line : dp)
    {
        for (const auto i : line)
        {
            std::cout << i << '\t';
        }
        std::cout << '\n';
    }


    std::cout << "result:\n";
    auto result = knapsackItems(dp, items);
    for (const auto& line : result)
    {
        for (const auto& i : line)
        {
            std::cout << i.name << '\t';
        }
        std::cout << '\n';
    }

    return 0;
}
