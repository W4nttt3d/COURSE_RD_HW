#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//A simple function
bool compareByLength(const std::string& str1, const std::string& str2)
{
    return str1.size() > str2.size();
}

//Functional object
class LengthComparator
{
public:
    bool operator()(const std::string& str1, const std::string& str2) const
    {
        return str1.size() > str2.size();
    }
};

//Task 2
unsigned int countDivisibleBy(const std::vector<int>& vec, int number)
{
    int count = count_if(vec.begin(), vec.end(), [number](int value) {return value % number == 0; });
    return count;
}

int main()
{
    //Task 1
    //A simple function
    std::vector<std::string> stringContainer = {"cpp", "vector", "class", "Functional objects", "lambda"};

    std::sort(stringContainer.begin(), stringContainer.end(), compareByLength);

    for (const std::string& str : stringContainer)
    {
        std::cout << str << std::endl;
    }

    std::cout << std::endl;
    //Functional object
    stringContainer = { "cpp", "vector", "class", "Functional objects", "lambda" };

    std::sort(stringContainer.begin(), stringContainer.end(), LengthComparator());

    for (const std::string& str : stringContainer)
    {
        std::cout << str << std::endl;
    }

    std::cout << std::endl;
    //Lambda function
    stringContainer = { "cpp", "vector", "class", "Functional objects", "lambda" };

    std::sort(stringContainer.begin(), stringContainer.end(), [](const std::string& str1, const std::string& str2){ return str1.size() > str2.size(); });

    for (const std::string& str : stringContainer)
    {
        std::cout << str << std::endl;
    }

    std::cout << std::endl;
    //Task 2
    int number;
    std::cout << "Enter numer: ";
    std::cin >> number;
    
    std::vector<int> vec;
    int input;
    std::cout << "Enter 10 numers: ";

    for (int i = 0; i < 10; i++)
    {
        std::cin >> input;
        vec.push_back(input);
    }

    std::cout << countDivisibleBy(vec, number);
}