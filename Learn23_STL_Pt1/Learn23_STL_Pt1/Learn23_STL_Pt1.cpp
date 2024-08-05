#include <iostream>
#include <sstream>
#include <string>

#include <set>
#include <map>
#include <stack>

// Task 1
unsigned int uniqueWordsCount(const std::string& line)
{
    std::set<std::string> setContainer;
    
    std::istringstream stream(line);
    std::string word;

    while (stream >> word)
    {
        setContainer.insert(word);
    }

    return setContainer.size();
}

std::string mostOccuredWord(const std::string& line)
{
    std::map<std::string, int> words;

    std::istringstream stream(line);
    std::string word;
    int countWord = 0;
    std::string mostWord;

    while (stream >> word)
    {
        words[word]++;
        if (words[word] > countWord)
        {
            countWord = words[word];
            mostWord = word;
        }
    }

    return mostWord;
}

// Task 3
bool bracketBalancingCheck(const std::string& line)
{
    std::stack<char> bracketsStack;

    for (char bracket : line)
    {
        if (bracket == '(' || bracket == '{' || bracket == '[')
        {
            bracketsStack.push(bracket);
        }
        else if (bracket == ')' || bracket == '}' || bracket == ']')
        {
            if (bracketsStack.empty() ||
                bracketsStack.top() != '(' && bracket == ')' ||
                bracketsStack.top() != '{' && bracket == '}' || 
                bracketsStack.top() != '[' && bracket == ']')
            {
                return false;
            }
            bracketsStack.pop();
        }
    }

    return true;
}

int main()
{
    std::string line = {"Hello Hey Hello Bye Hey Hello"};

    // Task 1
    std::cout << uniqueWordsCount(line) << std::endl;

    // Task 2
    std::cout << mostOccuredWord(line) << std::endl;

    // Task 3
    std::string line1 = "{ [()][ ] }()";
    std::string line2 = "[{]}";

    std::cout << (bracketBalancingCheck(line1) ? "OK" : "NOT OK") << std::endl;
    std::cout << (bracketBalancingCheck(line2) ? "OK" : "NOT OK") << std::endl;
}