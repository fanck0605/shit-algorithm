#include <iostream>
#include "stack.h"

int main()
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    std::cout << s.pop() << std::endl;
    std::cout << s.top() << std::endl;
    return 0;
}
