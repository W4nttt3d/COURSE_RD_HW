#include "DynamicIntArray.h"

#include <stdexcept>
#include <algorithm>

//default c-tor
DynamicIntArray::DynamicIntArray() : size(0), array(nullptr) {}

//c-tor with size
DynamicIntArray::DynamicIntArray(std::size_t size) : size(size), array(new int[size]()) {}

//copy c-tor
DynamicIntArray::DynamicIntArray(const DynamicIntArray& other) : size(other.size), array(new int[other.size]) 
{
	std::copy(other.array, other.array + other.size, array);
}

DynamicIntArray::~DynamicIntArray()
{
	delete[] array;
}

DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] array;

	size = other.size;
	array = new int[size];
	std::copy(other.array, other.array + other.size, array);

	return *this;
}

int& DynamicIntArray::operator[](std::size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Index out of range");
	}
	
	return array[index];
}

void DynamicIntArray::setSize(std::size_t newSize)
{
	int* newArray = new int[newSize]();
	std::size_t elementToCopy = std::min(size, newSize);
	std::copy(array, array + elementToCopy, newArray);

	delete[] array;
	array = newArray;
	size = newSize;
}

std::size_t DynamicIntArray::getSize() const
{
	return size;
}

void DynamicIntArray::clear()
{
	delete[] array;
	array = nullptr;
	size = 0;
}

bool DynamicIntArray::operator==(const DynamicIntArray& other)
{
	if (size != other.size)
	{
		return false;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (array[i] != other.array[i])
		{
			return false;
		}
	}

	return true;
}

bool DynamicIntArray::operator!=(const DynamicIntArray& other)
{
	return !(*this == other);
}

void DynamicIntArray::push_back(int element)
{
	int* newArray = new int[size + 1];
	std::copy(array, array + size, newArray);
	newArray[size] = element;

	delete[] array;
	array = newArray;
	size++;
}