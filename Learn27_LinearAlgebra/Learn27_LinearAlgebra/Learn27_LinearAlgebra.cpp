#include "Vector2d.h"
#include "Vector3d.h"

#include <iostream>

int main()
{
    //Vector2d()
    Vector2d vecFromPoints(1.0f, 2.0f, 4.0f, 6.0f);
    std::cout << "Vector from points (1.0, 2.0) to (4.0, 6.0): " << vecFromPoints << std::endl;

    //dotProduct()
    Vector2d v1(3.0f, 4.0f);
    Vector2d v2(1.0f, 0.0f);
    float dotProd = v1.dotProduct(v2);
    std::cout << "Dot product of " << v1 << " and " << v2 << " is: " << dotProd << std::endl;

    //negate()
    Vector2d negated = v1.negate();
    std::cout << "Negated vector of " << v1 << " is: " << negated << std::endl;

    //getRelativeState()
    Vector2d v3(3.0f, 4.0f);
    Vector2d v4(-3.0f, -4.0f);
    Vector2d v5(4.0f, -3.0f);

    auto state1 = v3.getRelativeState(v4);
    auto state2 = v3.getRelativeState(v5);
    auto state3 = v3.getRelativeState(v3);

    std::cout << "Relative state of " << v3 << " and " << v4 << ": " << v3.vectorRelativeStateToString(state1) << std::endl;
    std::cout << "Relative state of " << v3 << " and " << v5 << ": " << v3.vectorRelativeStateToString(state2) << std::endl;
    std::cout << "Relative state of " << v3 << " and " << v3 << ": " << v3.vectorRelativeStateToString(state3) << std::endl;

    //scale()
    Vector2d v6(1.0f, 2.0f);
    v6.scale(2.0f, 0.5f);
    std::cout << "Vector " << v6 << " after scaling by (2.0, 0.5): " << v6 << std::endl;

    //crossProduct()
    Vector3d v7(1.0f, 0.0f, 0.0f);
    Vector3d v8(0.0f, 1.0f, 0.0f);
    Vector3d crossProd = v7.crossProduct(v8);
    std::cout << "Cross product of " << v7 << " and " << v8 << " is: " << crossProd << std::endl;
}