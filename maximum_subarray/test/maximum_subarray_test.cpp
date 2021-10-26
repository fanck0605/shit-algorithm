#include <iostream>
#include <vector>
#include "maximum_subarray.h"

int main()
{
    std::vector<int> array{ -2,1,-3,4,-1,2,1,-5,4 };
    std::cout << maximumSubarray(array) << std::endl;

    return 0;
}
