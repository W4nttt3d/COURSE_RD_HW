#pragma once

#include <iostream>
#include <string>

enum class VectorRelativeState
{
	Identical,
	coDirected,
	OppositeDirected,
	AcuteAngle,
	ObtuseAngle,
	RightAngle
};

class Vector2d
{
public:
	Vector2d();
	Vector2d(float x, float y);
	Vector2d(float x0, float y0, float x1, float y1);
	~Vector2d();

	Vector2d& operator=(const Vector2d& other);

	//Vector2d operator+(const Vector2d& secondVector) const;
	//Vector2d operator-(const Vector2d& secondVector) const;

	friend Vector2d operator+(const Vector2d& leftVector, const Vector2d& rightVector);
	friend Vector2d operator-(const Vector2d& leftVector, const Vector2d& rightVector);

	void operator*=(float scalar);

	float operator()() const;

	float& operator[](std::size_t idx);

	friend std::ostream& operator<<(std::ostream& out, const Vector2d& vector);

	friend std::istream& operator>>(std::istream& in, Vector2d& vector);

	static unsigned getActiveInstanceCount();

	float dotProduct(const Vector2d& other) const;

	Vector2d negate() const;

	VectorRelativeState getRelativeState(const Vector2d& other) const;

	void scale(float factorX, float factorY);

	std::string vectorRelativeStateToString(VectorRelativeState state) const;

private:
	float x;
	float y;

	static unsigned activeInstanceCount;
};