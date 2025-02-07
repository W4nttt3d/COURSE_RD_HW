#include "Vector2d.h"

#include <iostream>

int main()
{
    //operator=;
    Vector2d vector1(1.0f, 2.0f);
    Vector2d vector2;

    vector2 = vector1;

    std::cout << "vector1: " << vector1 << std::endl;
    std::cout << "vector2: " << vector2 << std::endl;

    //Arithmetic operators
    vector2 = Vector2d(3.0f, 4.0f);

    Vector2d vector3 = vector1 + vector2;
    Vector2d vector4 = vector3 - vector1;
    std::cout << "vector3: " << vector3 << std::endl;
    std::cout << "vector4: " << vector4 << std::endl;

    //Scalar
    vector4 *= 5;
    std::cout << "vector4: " << vector4 << std::endl;

    //Length
    float length = vector4();
    std::cout << "Length of vector4: " << length << std::endl;

    //Index
    std::cout << "vector4[0] = " << vector4[0] << ", vector4[1] = " << vector4[1] << std::endl;

    //Input/output
    Vector2d inputVec;
    std::cout << "Enter vector coordinates (x y): ";
    std::cin >> inputVec;
    std::cout << "Input vector: " << inputVec << std::endl;

    std::cout << "Active instances of Vector2d: " << Vector2d::getActiveInstanceCount() << std::endl;
}
