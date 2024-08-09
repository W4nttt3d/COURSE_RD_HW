#pragma once

class Rectangle
{
public:
    Rectangle(); 
    Rectangle(float length, float height);

    float getArea();
    float getPerimeter() const; 

private:
    float m_length;
    float m_height;
};
