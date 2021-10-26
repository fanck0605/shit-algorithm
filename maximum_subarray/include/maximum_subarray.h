#pragma once
#include <vector>
#include <algorithm>

template <typename Iter>
std::iterator_traits<Iter>::value_type maximumSubarray(Iter begin, Iter end)
{
    if (begin == end) return {};

    Iter current = begin;

    auto prev = *current;
    auto max = prev;
    ++current;

    for (; current != end; ++current)
    {
        prev = std::max(prev + *current, *current);
        max = std::max(prev, max);
    }

    return max;
}
