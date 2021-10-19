#include <iostream>

template <typename DataType>
class Stack
{
public:
    Stack(const int maxSize = 100) : mSize(0), mMaxSize(maxSize)
    {
        std::cout << "Stack(const int)" << std::endl;
        mStack = new DataType[maxSize];
    }

    Stack(const Stack &src) : mSize(src.mSize), mMaxSize(src.mMaxSize)
    {
        std::cout << "Stack(const Stack &)" << std::endl;
        mStack = new DataType[mMaxSize];
        for (int i = 0; i < mSize; i++)
        {
            mStack[i] = src.mStack[i];
        }
    }

    Stack(Stack &&src) : mSize(src.mSize), mMaxSize(src.mMaxSize)
    {
        std::cout << "Stack(Stack &&)" << std::endl;
        mStack = src.mStack;
        src.mStack = nullptr;
    }

    ~Stack()
    {
        std::cout << "~Stack()" << std::endl;
        delete[] mStack;
    }

    Stack &operator=(const Stack &src)
    {
        std::cout << "Stack &operator=(const Stack &)" << std::endl;

        if (this == &src)
        {
            return *this;
        }

        mSize = src.mSize;
        mMaxSize = src.mMaxSize;

        delete[] mStack;
        mStack = new DataType[mMaxSize];

        for (int i = 0; i < mSize; i++)
        {
            mStack[i] = src.mStack[i];
        }

        return *this;
    }

    Stack &operator=(Stack &&src)
    {
        std::cout << "Stack operator=(Stack &&)" << std::endl;

        if (this == &src)
        {
            return *this;
        }

        mSize = src.mSize;
        mMaxSize = src.mMaxSize;

        delete[] mStack;
        mStack = src.mStack;
        src.mStack = nullptr;

        return *this;
    }

    void push(DataType e)
    {
        if (mSize < mMaxSize)
        {
            mStack[mSize] = std::move(e);
            mSize++;
        }
        else
        {
            throw std::overflow_error("stack is full");
        }
    }

    DataType pop()
    {
        return mStack[--mSize];
    }

    DataType top() const
    {
        return mStack[mSize - 1];
    }

    int size() const
    {
        return mSize;
    }

    int maxSize() const
    {
        return mMaxSize;
    }

private:
    DataType *mStack;
    int mSize;
    int mMaxSize;
};
