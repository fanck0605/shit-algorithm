#pragma once
#include <vector>
#include <functional>

// longest common subsequence length
template <typename Container>
std::vector<std::vector<size_t>> lcsLength(Container& seq1, Container& seq2)
{
    std::vector<std::vector<size_t>> dp(seq1.size() + 1, std::vector<size_t>(seq2.size() + 1, 0));

    for (size_t i = 0; i < seq1.size(); i++)
    {
        for (size_t j = 0; j < seq2.size(); j++)
        {
            if (seq1[i] == seq2[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else
            {
                dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    return dp;
}

// find longest common subsequence
std::vector<std::vector<size_t>> findLcs(const std::vector<std::vector<size_t>>& dp) {
    std::vector<std::vector<size_t>> result;

    const std::function<void(size_t, size_t, std::vector<size_t>)> findLcsHelper = [&dp, &result, &findLcsHelper](size_t i, size_t j, std::vector<size_t> current) mutable
    {
        if (i == 0 || j == 0)
        {
            result.push_back({ current.rbegin(),current.rend() });
            return;
        }

        if (dp[i - 1][j] == dp[i][j])
        {
            findLcsHelper(i - 1, j, current);
        }

        if (dp[i][j - 1] == dp[i][j])
        {
            findLcsHelper(i, j - 1, current);
        }

        if (dp[i - 1][j] != dp[i][j] && dp[i][j - 1] != dp[i][j])
        {
            current.push_back(i - 1);
            findLcsHelper(i - 1, j - 1, std::move(current));
        }
    };

    findLcsHelper(dp.size() - 1, dp[0].size() - 1, {});
    return result;
}
