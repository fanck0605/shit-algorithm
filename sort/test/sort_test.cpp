#include <iostream>
#include "sort.h"

int main()
{
    std::vector a{ 3,2,4,1,5 };

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

    std::cout << std::endl;
    return 0;
}
