#include <iostream>
#include "longest_common_subsequence.h"

int main()
{
    std::string seq1 = "ABCBDAB";
    std::string seq2 = "BDCABA";

    std::cout << "dp:\n";
    auto dp = lcsLength(seq1, seq2);
    for (auto line : dp)
    {
        for (auto i : line)
        {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "\nlongest common subsequence:\n";
    auto result = findLcs(dp, seq1, seq2);

    for (const auto& lcs : result)
    {
        for (const auto i : lcs)
        {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
