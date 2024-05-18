#include <iostream>
#include <numbers>

int main()
{
    // Task 1
    std::cout << "Task 1\n";

    std::cout << "Enter the time you spent in the game in seconds: ";
    int allSecondsTime;
    std::cin >> allSecondsTime;

    int hours;
    int minutes;
    int seconds;

    hours = allSecondsTime / 3600;
    minutes = (allSecondsTime % 3600) / 60;
    seconds = allSecondsTime % 60;

    std::cout << "hours: " << hours << ", minutes: " << minutes << ", seconds: " << seconds << std::endl << std::endl;

    // Task 2
    std::cout << "Task 2\n";
    
    std::cout << "Enter 3 numbers: ";
    double t2_num1, t2_num2, t2_num3;
    std::cin >> t2_num1 >> t2_num2 >> t2_num3;

    double sum = t2_num1 + t2_num2 + t2_num3;
    std::cout << "Sum: " << sum << std::endl;

    double product = t2_num1 * t2_num2 * t2_num3;
    std::cout << "Product: " << product << std::endl;

    double arithmeticMean = sum / 3; // (num1 + num2 + num3)/3
    std::cout << "Arithmetic mean: " << arithmeticMean << std::endl;

    // Method 1
    std::cout << std::boolalpha << "num1 <= num2: " << (t2_num1 <= t2_num2) << std::endl;
    std::cout << "num2 >= num3: " << (t2_num2 >= t2_num3) << std::endl;
    // Method 2
    if (t2_num1 == t2_num2)
    {
        std::cout << "num1 == num2" << std::endl;
    }
    else if(t2_num1 < t2_num2)
    {
        std::cout << "num1 < num2" << std::endl;
    }
    else
    {
        std::cout << "num1 > num2" << std::endl;
    }

    if (t2_num2 == t2_num3)
    {
        std::cout << "num2 == num3" << std::endl;
    }
    else if (t2_num2 < t2_num3)
    {
        std::cout << "num2 < num3" << std::endl;
    }
    else
    {
        std::cout << "num2 > num3" << std::endl;
    }
    
    // Task 3
    std::cout << "\nTask 3\n";

    std::cout << "Enter 2 numbers: ";
    float t3_num1, t3_num2;
    std::cin >> t3_num1 >> t3_num2;

    bool lessThan, equal, moreThan, lessOrEqual;
    lessThan = t3_num1 < t3_num2;
    equal = t3_num1 == t3_num2;
    moreThan = t3_num1 > t3_num2;
    lessOrEqual = t3_num1 <= t3_num2;

    // Method 1 (1/0)
    std::cout << std::noboolalpha << "lessThan: " << lessThan << ", equal: " << equal
        << ", moreThan: " << moreThan << ", lessOrEqual: " << lessOrEqual << std::endl;
    // Method 2 (true/false)
    std::cout << std::boolalpha << "lessThan: " << lessThan << ", equal: " << equal
        << ", moreThan: " << moreThan << ", lessOrEqual: " << lessOrEqual << std::endl << std::endl;

    // Task 4
    std::cout << "Task 4\n";

    std::cout << "Enter the width and height of the rectangle: ";
    float width = 0.0f, height = 0.0f;
    std::cin >> width >> height;

    float perimeter = (width + height) * 2;
    std::cout << "Perimeter: " << perimeter << std::endl;

    float areaRec = width * height;
    std::cout << "Area: " << areaRec << std::endl << std::endl;

    // Task 5
    std::cout << "Task 5\n";

    std::cout << "Enter the radius of the circle: ";
    float radius = 0.0f;
    std::cin >> radius;

    float length = 2 * std::numbers::pi * radius;
    std::cout << "length: " << length << std::endl;

    float areaÑir = std::numbers::pi * radius * radius;
    std::cout << "Area: " << areaÑir << std::endl;
}


