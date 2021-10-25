#include <iostream>
#include <algorithm>
#include <cassert>
#include "sort.h"

int main()
{
    std::vector toSort{ 16,4,10,14,1,9,3,2,8,7 };
    std::vector sorted = toSort;
    std::sort(sorted.begin(), sorted.end());

    std::cout << "to sort: ";
    for (auto i : toSort)
    {
        std::cout << i << ' ';
    }

    std::vector<int> result;

    std::cout << "\ninsert sort: ";

    result = insertSort(toSort);
    for (auto i : result)
    {
        std::cout << i << ' ';
    }
    assert(result == sorted);

    std::cout << "\nbubble sort: ";

    result = bubbleSort(toSort);
    for (auto i : result)
    {
        std::cout << i << ' ';
    }
    assert(result == sorted);

    std::cout << "\nquick sort: ";

    result = quickSort(toSort);
    for (auto i : result)
    {
        std::cout << i << ' ';
    }
    assert(result == sorted);

    std::cout << "\nheap sort: ";

    result = heapSort(toSort);
    for (auto i : result)
    {
        std::cout << i << ' ';
    }
    assert(result == sorted);

    std::cout << "\nmerge sort: ";

    result = mergeSort(toSort);
    for (auto i : result)
    {
        std::cout << i << ' ';
    }
    assert(result == sorted);

    std::cout << std::endl;
    return 0;
}
