#pragma once
#include <vector>
#include <algorithm>

template <typename Time>
auto flowShopScheduling(const std::vector<std::pair<Time, Time>>& jobs)
{
    std::vector<std::pair<Time, Time>> result(jobs.size());

    auto n1 = result.begin();
    auto n2 = result.end();
    for (const auto& job : jobs)
    {
        if (job.first < job.second)
        {
            *n1++ = job;
        }
        else
        {
            *--n2 = job;
        }
    }

    // n1 == n2 now
    std::sort(result.begin(), n1, [](auto a, auto b) { return a.first < b.first; });
    std::sort(n2, result.end(), [](auto a, auto b) { return a.second > b.second; });

    return result;
}

template <typename Time>
Time flowShopSchedulingTime(const std::vector<std::pair<Time, Time>>& scheduledJobs)
{
    Time flowA = 0;
    Time flowB = 0;

    for (const auto& i : scheduledJobs)
    {
        flowA += i.first;
        flowB = flowA > flowB ? flowA + i.second : flowB + i.second;
    }

    return flowB;
}
