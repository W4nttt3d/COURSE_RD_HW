#include "Rectangle.h"

#include <iostream>

Rectangle::Rectangle()
{
    std::cout << "Creating instance/object of class Rectangle";
}

Rectangle::Rectangle(float length, float height)
{
    m_length = length;
    m_height = height;
}

float Rectangle::getArea()
{
    return m_length * m_height;
}

float Rectangle::getPerimeter()
{
    return 2 * (m_length + m_height);
}
