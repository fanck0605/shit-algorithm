#pragma once
#include <vector>
#include <algorithm>

template <typename Container>
Container::value_type maximumSubarray(const Container& nums)
{
    using Data = typename Container::value_type;

    if (nums.empty())
        return {};

    Data prev{};
    Data max = nums[0];
    for (const Data& x : nums)
    {
        prev = std::max(prev + x, x);
        max = std::max(prev, max);
    }

    return max;
}
