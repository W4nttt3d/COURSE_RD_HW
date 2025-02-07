#pragma once
#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    //default c-tor
    DynamicArray();

    //c-tor with size
    DynamicArray(std::size_t size);

    //copy c-tor
    DynamicArray(const DynamicArray& other);

    //free allocated memory
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);

    T& operator[](std::size_t index);

    void setSize(std::size_t newSize);
    std::size_t getSize() const;

    void clear();

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    void push_back(const T& element);

    void reserve(std::size_t reservedSpace);
    std::size_t getCapacity() const;
    void shrinkToFit();

    void pop_back();
    T back() const;

private:
    std::size_t size;
    std::size_t capacity;
    T* array;
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(0), array(nullptr) {}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t size) : size(size), capacity(size), array(new T[size]()) {}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity), array(new T[other.capacity])
{
    std::copy(other.array, other.array + other.size, array);
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] array;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] array;
    
    size = other.size;
    capacity = other.capacity;
    array = new T[capacity];
    std::copy(other.array, other.array + other.size, array);
    
    return *this;
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Index out of range");
	}
	
	return array[index];
}

template <typename T>
void DynamicArray<T>::reserve(std::size_t reservedSpace)
{
    if (reservedSpace <= capacity)
    {
        return;
    }

    T* newArray = new T[reservedSpace]();
    std::copy(array, array + size, newArray);

    delete[] array;
    array = newArray;
    capacity = reservedSpace;
}

template <typename T>
void DynamicArray<T>::setSize(std::size_t newSize)
{
    if (newSize > capacity)
    {
        reserve(newSize);
    }
    else if (newSize < size)
    {
        std::fill(array + newSize, array + size, T());
    }

    size = newSize;
}

template <typename T>
std::size_t DynamicArray<T>::getSize() const
{
    return size;
}

template <typename T>
std::size_t DynamicArray<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
void DynamicArray<T>::clear()
{
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray& other) const
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

template <typename T>
bool DynamicArray<T>::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}

template <typename T>
void DynamicArray<T>::push_back(const T& element)
{
    if (size >= capacity)
    {
        reserve(capacity = 0 ? 1 : 2 * capacity);
    }

    array[size] = element;
    size++;
}

template <typename T>
void DynamicArray<T>::shrinkToFit()
{
    if (size < capacity)
    {
        T* newArray = new T[size]();
        std::copy(array, array + size, newArray);

        delete[] array;
        array = newArray;
        capacity = size;
    }
}

template <typename T>
void DynamicArray<T>::pop_back()
{
    if (size == 0)
    {
        throw std::out_of_range("Array is empty");
    }

    array[size] = T();
    size--;
}

template <typename T>
T DynamicArray<T>::back() const
{
    if (size == 0)
    {
        throw std::out_of_range("Array is empty");
    }

    return array[size - 1];
}