#include <iostream>
#include "sort.h"

int main()
{
    std::vector a{ 16,4,10,14,1,9,3,2,8,7 };

    std::cout << "to sort: ";
    for (auto i : a)
    {
        std::cout << i << ' ';
    }

    std::cout << "\ninsert sort: ";

    for (auto i : insertSort(a))
    {
        std::cout << i << ' ';
    }

    std::cout << "\nbubble sort: ";

    for (auto i : bubbleSort(a))
    {
        std::cout << i << ' ';
    }

    std::cout << "\nquick sort: ";

    for (auto i : quickSort(a))
    {
        std::cout << i << ' ';
    }

    std::cout << "\nheap sort: ";

    for (auto i : heapSort(a))
    {
        std::cout << i << ' ';
    }

    std::cout << std::endl;
    return 0;
}
