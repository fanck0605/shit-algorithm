#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <cassert>
#include <algorithm>
#include "avl_tree.h"

int main()
{
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_int_distribution<int32_t> uid(0, 1000);

    std::vector<int32_t> data;
    for (size_t i = 0; i < 1000; i++)
    {
        data.push_back(uid(randomEngine));
    }

    AvlTree<int32_t> avl;
    for (const auto i : data)
    {
        avl.insert(i);
    }

    std::vector<int32_t> result;
    avl.inOrderTraverse([&result](int32_t data)
        {
            result.push_back(data);
        });

    std::vector<int32_t> sorted = data;
    std::sort(sorted.begin(), sorted.end());

    std::vector<int32_t> nonDuplicate;
    std::unique_copy(sorted.begin(), sorted.end(), std::back_inserter(nonDuplicate));

    assert(result == nonDuplicate);
    assert(nonDuplicate.front() == avl.min());
    assert(nonDuplicate.back() == avl.max());

    std::cout << std::endl;
    return 0;
}
