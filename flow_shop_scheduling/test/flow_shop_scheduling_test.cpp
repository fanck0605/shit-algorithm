#include <iostream>
#include <vector>
#include "flow_shop_scheduling.h"

template <typename Time>
void showJobs(const std::vector<std::pair<Time, Time>>& jobs)
{
    for (const auto& i : jobs)
    {
        std::cout << i.first << ' ';
    }
    std::cout << std::endl;

    for (const auto& i : jobs)
    {
        std::cout << i.second << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::pair<int64_t, int64_t>> jobs{
        {5,2},
        {3,4},
        {6,7},
        {4,2},
        {8,9},
        {9,7},
        {6,3}
    };

    std::cout << "jobs:\n";
    showJobs(jobs);

    std::cout << "\nscheduled jobs:\n";
    auto scheduledJobs = flowShopScheduling(jobs);
    showJobs(scheduledJobs);

    std::cout << "\ntotal time: ";
    auto time = flowShopSchedulingTime(scheduledJobs);
    std::cout << time << std::endl;

    return 0;
}
