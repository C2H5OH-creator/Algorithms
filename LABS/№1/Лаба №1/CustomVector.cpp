#include "CustomVector.h"

template <typename T>
CustomVector<T>::CustomVector(size_t initialCapacity) : size(0), capacity(initialCapacity) {
    array = new T[capacity];
}

template <typename T>
CustomVector<T>::~CustomVector() {
    delete[] array;
}

template <typename T>
void CustomVector<T>::Resize(size_t newCapacity) {
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size; ++i) {
        newData[i] = array[i];
    }

    delete[] array;
    array = newData;
    capacity = newCapacity;
}

template <typename T>
void CustomVector<T>::PushBack(const T& value) {
    if (size == capacity) {
        Resize(capacity * 2);
    }
    array[size] = value;
    size++;
}

template <typename T>
void CustomVector<T>::PopBack() {
    if (size > 0) {
        size--;
    }
    else {
        throw std::out_of_range("Массив пуст!");
    }
}

template <typename T>
T& CustomVector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Вышли за границы массива!");
    }
    return array[index];
}

template <typename T>
size_t CustomVector<T>::GetSize() const {
    return size;
}

template <typename T>
size_t CustomVector<T>::GetCapacity() const {
    return capacity;
}

template <typename T>
void CustomVector<T>::Print() const {
    for (size_t i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}