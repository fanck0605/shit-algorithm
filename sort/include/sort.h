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

template <typename DataType>
std::vector<DataType> heapSort(std::vector<DataType> toSort)
{
    auto begin = toSort.begin();
    auto end = toSort.end();
    buildMaxHeap2(begin, end);

    for (auto i = end - 1; i != begin; --i)
    {
        std::iter_swap(begin, i);
        maxHeapify(begin, i, begin);
    }

    return toSort;
}

template<typename Iter>
void buildMaxHeap(Iter begin, Iter end)
{
    auto length = end - begin;
    if (length < 2) return;

    Iter i = begin + length / 2 - 1;
    for (;;)
    {
        maxHeapify(begin, end, i);
        if (i == begin) return;
        --i; // to be optimized
    }
}

template <typename Iter>
void maxHeapify(Iter begin, Iter end, Iter start)
{
    const size_t sizeHalf = (end - begin) / 2;
    Iter parent = start;
    while (true) {
        size_t parentIndex = parent - begin;

        if (parentIndex >= sizeHalf) return; // parent is a leaf

        Iter largest = parent;

        Iter leftChild = begin + parentIndex * 2 + 1;
        if (*leftChild > *largest) // we must have a left child
        {
            largest = leftChild;
        }

        Iter rightChild = leftChild + 1;
        if (rightChild != end && *rightChild > *largest)
        {
            largest = rightChild;
        }

        if (largest == parent) return;

        std::iter_swap(largest, parent);
        parent = largest;
    }
}

// the last element is the newly inserted
template <typename Iter>
void maxHeapify2(Iter begin, Iter last)
{
    Iter changed = last;
    while (changed != begin)
    {
        Iter parent = begin + (changed - begin - 1) / 2;
        if (*changed > *parent)
        {
            std::iter_swap(changed, parent);
            changed = parent;
        }
        else
        {
            break;
        }
    }
}

template<typename Iter>
void buildMaxHeap2(Iter begin, Iter end)
{
    auto length = end - begin;
    if (length < 2) return;

    for (auto i = begin + 1; i != end; i++)
    {
        maxHeapify2(begin, i);
    }
}
