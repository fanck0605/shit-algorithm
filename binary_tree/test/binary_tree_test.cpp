#include <iostream>
#include <memory>
#include <vector>

#include "binary_tree.h"

int main()
{

    BinaryTree<int> tree;

    std::vector<std::string> input{"1", "2", "end", "6", "end", "end", "3", "4", "end", "end", "5", "end", "end"};

    auto generator = [current = input.begin(), end = input.end()]() mutable
    {
        if (current == end)
        {
            throw std::range_error("invalid iterator");
        }

        const auto &data = *current;
        current += 1;

        std::cout << data << std::endl;

        if (data == "end")
        {
            return std::unique_ptr<int>{nullptr};
        }
        return std::unique_ptr<int>(new int{std::atoi(data.data())});
    };

    tree.createTreePreOrder(generator);

    std::cout << "\npreOrder: ";
    tree.preOrderTraverse([](int e)
                          { std::cout << e << ' '; });

    std::cout << "\nnonTraverse: ";
    tree.preOrderTraverseNonRecursive([](int e)
                                      { std::cout << e << ' '; });

    std::cout << "\ninOrder: ";
    tree.inOrderTraverse([](int e)
                         { std::cout << e << ' '; });

    std::cout << "\nnonTraverse: ";
    tree.inOrderTraverseNonRecursive([](int e)
                                     { std::cout << e << ' '; });

    std::cout << "\npostOrder: ";
    tree.postOrderTraverse([](int e)
                           { std::cout << e << ' '; });

    std::cout << "\nnonTraverse: ";
    tree.postOrderTraverseNonRecursive([](int e)
                                       { std::cout << e << ' '; });

    std::cout << "\nlevelOrder: ";
    tree.levelOrderTraverse([](int e)
                            { std::cout << e << ' '; });

    std::cout << std::endl;

    return 0;
}
