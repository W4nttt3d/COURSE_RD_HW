#include "Vector2d.h"

#include <cmath>

unsigned Vector2d::activeInstanceCount = 0;

Vector2d::Vector2d() : x(0.0), y(0.0)
{
	++activeInstanceCount;
}

Vector2d::Vector2d(float x, float y) : x(x), y(y)
{
	++activeInstanceCount;
}

Vector2d::Vector2d(float x0, float y0, float x1, float y1) : x(x1 - x0), y(y1 - y0)
{
	++activeInstanceCount;
}

Vector2d::~Vector2d()
{
	--activeInstanceCount;
}

Vector2d& Vector2d::operator=(const Vector2d& other)
{
	if (this == &other)
	{
		return *this;
	}
	else
	{
		x = other.x;
		y = other.y;
		return *this;
	}
}

//Vector2d Vector2d::operator+(const Vector2d& secondVector) const
//{
//	return Vector2d(x + secondVector.x, y + secondVector.y);
//}
//
//Vector2d Vector2d::operator-(const Vector2d& secondVector) const
//{
//	return Vector2d(x - secondVector.x, y - secondVector.y);
//}

Vector2d operator+(const Vector2d& leftVector, const Vector2d& rightVector)
{
	return Vector2d(leftVector.x + rightVector.x, leftVector.y + rightVector.y);
}

Vector2d operator-(const Vector2d& leftVector, const Vector2d& rightVector)
{
	return Vector2d(leftVector.x - rightVector.x, leftVector.y - rightVector.y);
}

void Vector2d::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vector2d::operator()() const
{
	return std::sqrt(x * x + y * y);
}

float& Vector2d::operator[](std::size_t idx) {
	if (idx == 0) { return x; }
	else if (idx == 1) { return y; }
	else { throw std::out_of_range("Index out of range"); }
}

std::ostream& operator<<(std::ostream& out, const Vector2d& vector)
{
	out << "{" << vector.x << "; " << vector.y << "}";
	return out;
}

std::istream& operator>>(std::istream& in, Vector2d& vector)
{
	in >> vector.x >> vector.y;
	return in;
}

unsigned Vector2d::getActiveInstanceCount()
{
	return  activeInstanceCount;
}

float Vector2d::dotProduct(const Vector2d& other) const
{
	return (x * other.x) + (y * other.y);
}

Vector2d Vector2d::negate() const
{
	return Vector2d(-x, -y);
}

VectorRelativeState Vector2d::getRelativeState(const Vector2d& other) const
{
	float dotProduct = this->dotProduct(other);
	float lengthProduct = (*this)() * other();

	if (lengthProduct == 0)
	{
		return VectorRelativeState::Identical;
	}

	float cos = dotProduct / lengthProduct;

	if (cos == 1.0f)
	{
		return VectorRelativeState::coDirected;
	}
	else if (cos == -1.0f)
	{
		return VectorRelativeState::OppositeDirected;
	}
	else if (cos == 0.0f)
	{
		return VectorRelativeState::RightAngle;
	}
	else if (cos > 0.0f)
	{
		return VectorRelativeState::AcuteAngle;
	}
	else
	{
		return VectorRelativeState::ObtuseAngle;
	}
}

std::string Vector2d::vectorRelativeStateToString(VectorRelativeState state) const
{
	switch (state)
	{
	case VectorRelativeState::Identical:
		return "Identical";
	case VectorRelativeState::coDirected:
		return "Co-directed";
	case VectorRelativeState::OppositeDirected:
		return "Opposite Directed";
	case VectorRelativeState::AcuteAngle:
		return "Acute Angle";
	case VectorRelativeState::ObtuseAngle:
		return "Obtuse Angle";
	case VectorRelativeState::RightAngle:
		return "Right Angle";
	default:
		return "Unknown State";
	}
}

void Vector2d::scale(float factorX, float factorY)
{
	x *= factorX;
	y *= factorY;
}