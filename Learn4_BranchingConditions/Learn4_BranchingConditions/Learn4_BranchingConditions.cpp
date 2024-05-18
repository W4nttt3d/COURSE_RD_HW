#include <iostream>

int main()
{
    // Task 1
    std::cout << "Task 1\n";

    std::cout << "Enter 3 numbers: ";
    double t1_num1, t1_num2, t1_num3;
    std::cin >> t1_num1 >> t1_num2 >> t1_num3;

    double maxNum = t1_num1;

    if (t1_num2 > maxNum)
    {
        maxNum = t1_num2;
    }
    if (t1_num3 > maxNum)
    {
        maxNum = t1_num3;
    }

    std::cout << "Max num: " << maxNum << std::endl;

   /* if (t1_num1 > t1_num2 && t1_num1 > t1_num3)
    {
        std::cout << "Max num: " << t1_num1 << std::endl;
    }
    else if (t1_num2 > t1_num1 && t1_num2 > t1_num3)
    {
        std::cout << "Max num: " << t1_num2 << std::endl;
    }
    else
    {
        std::cout << "Max num: " << t1_num3 << std::endl;
    }*/


    std::cout << std::endl;

    // Task 2
    std::cout << "Task 2\n";

    std::cout << "Enter 2 numbers: ";
    double t2_num1, t2_num2;
    std::cin >> t2_num1 >> t2_num2;

    double res = (t2_num1 < t2_num2) ? t2_num1 : t2_num2;
    std::cout << "Result: " << res << std::endl << std::endl;

    // Task 3
    std::cout << "Task 3\n";

    std::cout << "Enter number: ";
    int t3_num1;
    std::cin >> t3_num1;
    //Metod 1
    if (t3_num1 % 5 == 0 && t3_num1 % 11 == 0)
    {
        std::cout << "The number " << t3_num1 << " is evenly divisible by 5 and 11" << std::endl;
    }
    else if (t3_num1 % 5 == 0)
    {
        std::cout << "The number " << t3_num1 << " is exactly divisible by 5" << std::endl;
    }
    else if (t3_num1 % 11 == 0)
    {
        std::cout << "The number " << t3_num1 << " is exactly divisible by 11" << std::endl;
    }
    else
    {
        std::cout << "The number " << t3_num1 << " is not exactly divisible by 5 and 11" << std::endl;
    }
    //Metod 2
    if (t3_num1 % 5 == 0)
    {
        if (t3_num1 % 11 == 0)
        {
            std::cout << "The number " << t3_num1 << " is evenly divisible by 5 and 11" << std::endl;
        }
        else
        {
            std::cout << "The number " << t3_num1 << " is exactly divisible by 5" << std::endl;
        }
    }
    else if (t3_num1 % 11 == 0)
    {
        std::cout << "The number " << t3_num1 << " is exactly divisible by 11" << std::endl;
    }
    else
    {
        std::cout << "The number " << t3_num1 << " is not exactly divisible by 5 and 11" << std::endl;
    }

    std::cout << std::endl;

    // Task 4
    std::cout << "Task 4\n";

    std::cout << "Enter values for 3 angles: ";
    float angle1, angle2, angle3;
    std::cin >> angle1 >> angle2 >> angle3;

    float sumAngles = angle1 + angle2 + angle3;

    if (sumAngles != 180 || angle1 <= 0 || angle2 <= 0 || angle3 <= 0)
    {
        std::cout << "These 3 angles do not form a triangle" << std::endl << 
            "The angles cannot be <= 0 and their sum must equal 180 degrees";
    }
    else
    {
        std::cout << "These 3 angles form a triangle";
    }

    std::cout << std::endl << std::endl;

    // Task 5
    std::cout << "Task 5\n";
    enum class listMonth
    {
        January = 1,
        February = 2,
        March = 3,
        April = 4,
        May = 5,
        June = 6,
        July = 7,
        August = 8,
        September = 9,
        October = 10,
        November = 11,
        December = 12
    };

    std::cout << "Enter the month number: ";
    int numberMonth;
    std::cin >> numberMonth;

    //Metod 1
    listMonth Month = static_cast<listMonth>(numberMonth);

    //Metod 2
    switch (numberMonth)
    {
    case 1:
        Month = listMonth::January;
        break;
    case 2:
        Month = listMonth::February;
        break;
    case 3:
        Month = listMonth::March;
        break;
    case 4:
        Month = listMonth::April;
        break;
    case 5:
        Month = listMonth::May;
        break;
    case 6:
        Month = listMonth::June;
        break;
    case 7:
        Month = listMonth::July;
        break;
    case 8:
        Month = listMonth::August;
        break;
    case 9:
        Month = listMonth::September;
        break;
    case 10:
        Month = listMonth::October;
        break;
    case 11:
        Month = listMonth::November;
        break;
    case 12:
        Month = listMonth::December;
        break;
    }

    switch (Month)
    {
    case listMonth::January:
        std::cout << "January";
        break;
    case listMonth::February:
        std::cout << "February";
        break;
    case listMonth::March:
        std::cout << "March";
        break;
    case listMonth::April:
        std::cout << "April";
        break;
    case listMonth::May:
        std::cout << "May";
        break;
    case listMonth::June:
        std::cout << "June";
        break;
    case listMonth::July:
        std::cout << "July";
        break;
    case listMonth::August:
        std::cout << "August";
        break;
    case listMonth::September:
        std::cout << "September";
        break;
    case listMonth::October:
        std::cout << "October";
        break;
    case listMonth::November:
        std::cout << "November";
        break;
    case listMonth::December:
        std::cout << "December";
        break;
    default:
        std::cout << "Such a month does not exist";
        break;
    }

    std::cout << std::endl << std::endl;

    //Task 6
    std::cout << "Task 6\n";
    std::cout << "Enter the month number: ";
    int numMonth;
    std::cin >> numMonth;

    switch (numMonth)
    {
    case 12:
    case 1:
    case 2:
        std::cout << "Winter";
        break;
    case 3:
    case 4:
    case 5:
        std::cout << "Spring";
        break;
    case 16:
    case 7:
    case 8:
        std::cout << "Summer";
        break;
    case 9:
    case 10:
    case 11:
        std::cout << "Autumn";
        break;
    default:
        std::cout << "Such a month does not exist";
        break;
    }
}