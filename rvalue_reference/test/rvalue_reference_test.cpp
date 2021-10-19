#include <iostream>
#include "stack.h"

Stack<int> getStack(const Stack<int> &stack)
{
    Stack<int> tmp(stack.maxSize());
    return tmp;
}

int main()
{
    Stack<int> s;
    Stack<int> s1 = s;
    Stack<int> s2 = getStack(s);
    s2 = getStack(s);
    const Stack<int> &s3 = getStack(s);
    return 0;
}
