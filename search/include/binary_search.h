#pragma once

template <typename Iterator, typename DataType>
Iterator binarySearch(const Iterator begin, const Iterator end, const DataType key)
{
    Iterator left = begin;
    Iterator right = end;

    while (left < right)
    {
        Iterator middle = left + (right - left) / 2;

        if (key < *middle)
        {
            right = middle;
        }
        else if (key > *middle)
        {
            left = middle + 1;
        }
        else // if (*middle == key)
        {
            return middle;
        }
    }

    return end;
}


using ElemType = int;
int binarySearchBad(std::vector<ElemType> arr, ElemType key)
{
    int low = 0;
    int high = arr.size() - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key < arr[mid])
        {
            high = mid - 1;
        }
        else if (key > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}
