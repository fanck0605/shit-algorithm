#pragma once
#include <algorithm>
#include <functional>
#include <utility>

struct KnapsackItem
{
    using Value = size_t;
    using Weight = size_t;

    size_t name;
    Value value;
    Weight weight;
};

template <typename Container>
auto knapsackValue(const Container& items, typename Container::value_type::Weight maxCapacity)
{
    using Value = typename Container::value_type::Value;
    using Capacity = typename Container::value_type::Weight;

    std::vector<std::vector<Value>> dp(items.size() + 1, std::vector<Value>(maxCapacity + 1, 0));

    for (size_t i = 1; i <= items.size(); i++)
    {
        auto value = items[i - 1].value;
        auto weight = items[i - 1].weight;

        for (Capacity capacity = 1; capacity < weight; ++capacity)
        {
            dp[i][capacity] = dp[i - 1][capacity];
        }
        for (Capacity capacity = weight; capacity <= maxCapacity; ++capacity)
        {
            dp[i][capacity] = std::max(dp[i - 1][capacity], dp[i][capacity - weight] + value);
        }
    }

    return dp;
}


template <typename Container>
std::vector<Container> knapsackItems(const std::vector<std::vector<typename Container::value_type::Value>>& dp, const Container& items)
{
    std::vector<Container> result;

    const std::function<void(size_t, size_t, Container)> knapsackItemsHelper = [&](size_t i, size_t j, Container current) {
        if (dp[i][j] == 0) {
            result.push_back(std::move(current));
            return;
        }

        if (dp[i][j] == dp[i - 1][j]) {
            knapsackItemsHelper(i - 1, j, current);
        }

        auto value = items[i - 1].value;
        auto weight = items[i - 1].weight;

        if (j >= weight && dp[i - 1][j - weight] == dp[i][j] - value) {
            current.push_back(items[i - 1]);
            knapsackItemsHelper(i - 1, j - weight, std::move(current));
        }
    };

    knapsackItemsHelper(dp.size() - 1, dp[0].size() - 1, {});

    return result;
}
