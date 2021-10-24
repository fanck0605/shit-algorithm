#pragma once
#include <vector>

template <typename DataType>
std::vector<DataType> insertSort(std::vector<DataType> toSort)
{
    toSort.push_back({});

    const auto rbegin = std::rbegin(toSort);
    const auto rend = std::rend(toSort);

    for (auto i = rbegin + 2; i != rend; ++i)
    {
        *rbegin = *i;
        for (auto j = i; *j > *(j - 1); --j)
        {
            std::iter_swap(j, j - 1);
        }
    }

    toSort.pop_back();

    return toSort;
}

template <typename DataType>
std::vector<DataType> bubbleSort(std::vector<DataType> toSort)
{
    const auto begin = toSort.begin();
    const auto end = toSort.end();

    for (auto i = begin; i != end; ++i)
    {
        bool swap = false;
        for (auto j = end - 1; j != i; --j)
        {
            if (*j < *(j - 1))
            {
                swap = true;
                std::iter_swap(j, j - 1);
            }
        }
        if (!swap)
            break;
    }

    return toSort;
}

template <typename DataType>
std::vector<DataType> quickSort(std::vector<DataType> toSort)
{
    quickSortHelper(toSort.begin(), toSort.end());
    return toSort;
}

template<typename Iterator>
Iterator quickSortPartition(Iterator begin, Iterator end)
{
    auto pivot = *begin;
    auto left = begin;
    auto right = end;

    while (left != right)
    {
        while (*--right >= pivot && right != left);

        *left = *right;

        while (right != left && *++left <= pivot);

        *right = *left;
    }

    *left = pivot;

    return left;
}

template <typename Iterator>
void quickSortHelper(Iterator begin, Iterator end)
{
    if (begin == end) return;
    if (begin + 1 == end) return;

    Iterator pivot = quickSortPartition(begin, end);
    quickSortHelper(begin, pivot);
    quickSortHelper(pivot + 1, end);
}
