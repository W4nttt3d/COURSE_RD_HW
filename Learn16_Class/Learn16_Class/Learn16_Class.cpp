#include <iostream>
#include "Rectangle.h"

int main()
{
    //Default c-tor
    std::cout << "---Default c-tor---" << std::endl;
    Rectangle rectangle1;

    std::cout << std::endl << std::endl;

    //Parameterized c-tor
    std::cout << "---Parameterized c-tor---" << std::endl;

    float length;
    float height;

    std::cout << "Enter length and height: ";
    std::cin >> length >> height;

    Rectangle rectangle2(length, height);
    std::cout << "Area: " << rectangle2.getArea() << std::endl;
    std::cout << "Perimeter: " << rectangle2.getPerimeter() << std::endl;
}
