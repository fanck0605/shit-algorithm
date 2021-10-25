#pragma once
#include <vector>
#include <functional>

// longest common subsequence length
template <typename Container>
std::vector<std::vector<size_t>> lcsLength(const Container& seq1, const Container& seq2)
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
template <typename Container>
std::vector<Container> findLcs(const std::vector<std::vector<size_t>>& dp, const Container& seq1, const Container& seq2) {
    std::vector<Container> result;

    const std::function<void(size_t, size_t, Container)> findLcsHelper = [&](size_t i, size_t j, Container current) mutable
    {
        if (dp[i][j] == 0)
        {
            std::reverse(current.begin(), current.end());
            result.push_back(std::move(current));
            return;
        }

        if (seq1[i - 1] == seq2[j - 1])
        {
            current.push_back(seq1[i - 1]);
            findLcsHelper(i - 1, j - 1, std::move(current));
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
    };

    findLcsHelper(dp.size() - 1, dp[0].size() - 1, {});
    return result;
}
