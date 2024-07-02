#include <iostream>
#include <string>
#include <algorithm>

const unsigned Number_Students = 4;
const unsigned Number_Grades = 4;

struct Student
{
    std::string name;
    unsigned marks[Number_Grades];
};


//Task 1
double calculateAverage(const Student& student, unsigned numberGrades)
{
    double sum = 0;
    for (int i = 0; i < numberGrades; i++)
    {
        sum += student.marks[i];
    }

    return sum / numberGrades;
}

void printAverage(Student* students, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "Student: " << students[i].name << "\t\tAverage marks: " << calculateAverage(students[i], Number_Grades) << std::endl;
    }
}

//Task 2
bool compare(const Student& student1, const Student& student2)
{
    return calculateAverage(student1, Number_Grades) > calculateAverage(student2, Number_Grades);
}

void sort(Student* students, unsigned size)
{
    std::sort(students, students + size, compare);
}

//Task 3
Student* getTopStudent(Student* students, unsigned size)
{
    if (size == 0) return nullptr;
    
    //Method 1
    sort(students, Number_Students);
    Student* topStudent = &students[0];

    //Method 2
    /*Student* topStudent = &students[0];
    double highestAverage = calculateAverage(students[0], Number_Grades);

    for (unsigned i = 1; i < size; ++i)
    {
        double currentAverage = calculateAverage(students[i], Number_Grades);
        if (currentAverage > highestAverage)
        {
            highestAverage = currentAverage;
            topStudent = &students[i];
        }
    }*/

    return topStudent;
}

//Task 4
int countStudents(Student* students, int size)
{
    unsigned averageScore;
    std::cout << "Enter the average score: ";
    std::cin >> averageScore;
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (calculateAverage(students[i], size) > averageScore)
        {
            count++;
        }
    }

    return count;
}

//Task 5
void getBestStudents(Student* inStudents, unsigned inSize, Student* outStudents, unsigned& outSize, unsigned percent)
{
    sort(inStudents, inSize);

    outSize = (percent * inSize) / 100;

    for (int i = 0; i < outSize; i++)
    {
        outStudents[i] = inStudents[i];
    }
}

int main()
{
    //Task 1
    Student students[Number_Students] =
    {
        {"Vlad", {5, 5, 4, 5}}, 
        {"Nazar", {5, 4, 3, 3}}, 
        {"Yaroslav", {5, 5, 4, 3}},
        {"Vadim", {4, 3, 3, 3}}
    };

    printAverage(students, Number_Students);
    
    std::cout << std::endl << std::endl;

    //Task 2
    sort(students, Number_Students);
    printAverage(students, Number_Students);

    std::cout << std::endl << std::endl;

    //Task 3
    std::cout << "Address: " << getTopStudent(students, Number_Students);

    std::cout << std::endl << std::endl;

    //Task 4
    std::cout << countStudents(students, Number_Students);

    std::cout << std::endl << std::endl;

    //Task 5
    unsigned outSize = 0;
    Student outStudents[Number_Students];

    unsigned percent;
    std::cout << "Enter the percent: ";
    std::cin >> percent;

    getBestStudents(students, Number_Students, outStudents, outSize, percent);
    printAverage(outStudents, outSize);
}
