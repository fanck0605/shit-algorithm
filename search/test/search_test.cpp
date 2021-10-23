#include <iostream>
#include <vector>
#include "binary_search.h"

int main()
{
    std::vector<int> vec{ 1,2,3,4,5 };

    for (const auto i : vec)
    {
        std::cout << i << ' ';
    }

    const int key = 2;
    std::cout << "\nbinary search: " << key << '\n';
    std::cout << "index: " << binarySearch(vec.begin(), vec.end(), key) - vec.begin() << '\n';

    std::cout << "binary search bad: " << key << '\n';
    std::cout << "index: " << binarySearchBad(vec, key) << std::endl;

    return 0;
}
