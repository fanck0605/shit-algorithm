#include <vector>
#include "rb_tree.h"

int main()
{
    RbTree<int> rbTree;

    std::vector<int> data{ 1,2,3,4,5,6,7,8,9,10 };

    for (const auto i : data)
    {
        rbTree.insert(i);
    }

    return 0;
}