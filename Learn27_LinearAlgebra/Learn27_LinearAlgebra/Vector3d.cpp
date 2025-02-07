#include "Vector3d.h"

Vector3d::Vector3d() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3d::Vector3d(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3d::~Vector3d() {}

Vector3d Vector3d::crossProduct(const Vector3d& other) const
{
    return Vector3d(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

std::ostream& operator<<(std::ostream& out, const Vector3d& vector)
{
	out << "{" << vector.x << "; " << vector.y << "; " << vector.z << "}";
	return out;
}