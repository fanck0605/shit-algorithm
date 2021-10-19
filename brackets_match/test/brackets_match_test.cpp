#include <iostream>
#include <vector>
#include <map>

int main()
{
    std::string bracketList = "([{}])";
    std::map<char, char> bracketPairs{{'{', '}'}, {'[', ']'}, {'(', ')'}};

    std::vector<char> leftBracketStack;
    for (const auto ch : bracketList)
    {
        char leftBracket;
        char rightBracket;
        switch (ch)
        {
        case '{':
        case '[':
        case '(':
            leftBracketStack.push_back(ch);
            break;
        case '}':
        case ']':
        case ')':
            if (leftBracketStack.empty())
            {
                std::cout << "lack left bracket!" << std::endl;
                return 0;
            }

            leftBracket = leftBracketStack.back();
            rightBracket = bracketPairs[leftBracket];
            if (rightBracket != ch)
            {
                std::cout << "not match!" << std::endl;
                std::cout << "except: " << rightBracket << std::endl;
                std::cout << "result: " << ch << std::endl;
                return 0;
            }

            leftBracketStack.pop_back();
            break;
        default:
            break;
        }
    }

    if (!leftBracketStack.empty())
    {
        std::cout << "lack right bracket!";
        return 0;
    }

    std::cout << "match success!" << std::endl;
    return 0;
}
