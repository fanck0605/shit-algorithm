#include <iostream>
#include <vector>
#include <cassert>
#include "maximum_subarray.h"

int main()
{
    std::vector<int> array{ -2,1,-3,4,-1,2,1,-5,4 };

    std::cout << "array: ";
    for (const auto& i : array)
    {
        std::cout << i << ' ';
    }

    std::cout << "\nmaximum subarray sum: ";
    auto maxSum = maximumSubarray(array.begin(), array.end());
    std::cout << maxSum << std::endl;

    assert(maxSum == 6);

    return 0;
}
