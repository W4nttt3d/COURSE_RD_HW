#include <iostream>
#include <iomanip>

enum class daysWeek
{
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5, 
    Saturday = 6,
    Sunday = 7
};

int main()
{
    // Завдання 1
    std::cout << "\tTask 1" << std::endl << std::endl;

    int A;
    std::cout << "Enter integer 1: ";
    std::cin >> A;
    
    int B;
    std::cout << "Enter integer 2: ";
    std::cin >> B;

    int x = A;
    A = B;
    B = x;

    std::cout << "\nInteger 1: " << A;
    std::cout << "\nInteger 2: " << B;

    // Завдання 2
    std::cout << "\n\n\tTask 2" << std::endl << std::endl;

    double Y = 3.1415926535897914159265358979;
    std::cout << "double: " << Y << std::endl;
    std::cout << "double in int: " << int(Y) << std::endl;
    std::cout << std::setw(20) << std::right << std::setfill('$') << "W20: " << Y << std::endl;

    // Завдання 3
    std::cout << "\n\n\tTask 3" << std::endl << std::endl;

    std::cout << std::setprecision(3) << Y << std::endl;
    std::cout << std::setprecision(6) << Y << std::endl;
    std::cout << std::setprecision(11) << Y << std::endl;

    std::cout << std::endl;

    std::cout << std::scientific << std::setprecision(3) << Y << std::endl;
    std::cout << std::scientific << std::setprecision(6) << Y << std::endl;
    std::cout << std::scientific << std::setprecision(11) << Y << std::endl;

    // Завдання 4
    std::cout << "\n\n\tTask 4" << std::endl << std::endl;

    std::cout << "Monday: " << int(daysWeek::Monday) << std::endl;
    std::cout << "Tuesday: " << int(daysWeek::Tuesday) << std::endl;
    std::cout << "Wednesday: " << int(daysWeek::Wednesday) << std::endl;
    std::cout << "Thursday: " << int(daysWeek::Thursday) << std::endl;
    std::cout << "Friday: " << int(daysWeek::Friday) << std::endl;
    std::cout << "Saturday: " << int(daysWeek::Saturday) << std::endl;
    std::cout << "Sunday: " << int(daysWeek::Sunday) << std::endl;

    // Завдання 5
    std::cout << "\n\n\tTask 5" << std::endl << std::endl;

    int boolean;
    std::cout << "Enter number: ";
    std::cin >> boolean;

    std::cout << std::boolalpha << "Boolean: " << bool(boolean) << std::endl;
}

