#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class CustomVector {
public:
    //Конструтор вектора
    CustomVector(size_t initialCapacity = 2);
    ~CustomVector();

    //Добавить элемент в конец массива
    void PushBack(const T& value);

    //Вырезать элемент с конца массива
    void PopBack();

    //Перегрузка оператора чтобы обращатся по индексам как обычно
    T& operator[](size_t index);

    //Получения размера вектора
    size_t GetSize() const;

    //Получение вместимости
    size_t GetCapacity() const;

    //Печать массива
    void Print() const;

    //Класс функций, чтобы работал синтаксис типа (const auto& item : vector)
    T* begin() { return array; }

    T* end() { return array + size; }

    const T* begin() const { return array; }

    const T* end() const { return array + size; }

private:
	T* array;   //Указатель на массив
	size_t size;    //Размер массиа
    size_t capacity;    //Вместимость массива

    void Resize(size_t newCapacity); //Функция изменения размера массива
};