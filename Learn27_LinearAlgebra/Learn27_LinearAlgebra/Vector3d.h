#pragma once

#include <iostream>

class Vector3d
{
public:
    Vector3d();
    Vector3d(float x, float y, float z);
    ~Vector3d();

    Vector3d crossProduct(const Vector3d& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector3d& vector);

private:
    float x;
    float y;
    float z;
};

