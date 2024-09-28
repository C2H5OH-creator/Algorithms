#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class CustomVector {
public:
    CustomVector(size_t initialCapacity = 2);
    ~CustomVector();

    void PushBack(const T& value);

    void PopBack();

    T& operator[](size_t index);

    size_t GetSize() const;

    size_t GetCapacity() const;

    void Print() const;

private:
	T* array;
	size_t size;
    size_t capacity;

    void Resize(size_t newCapacity);
};