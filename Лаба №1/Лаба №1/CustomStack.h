#pragma once

#include "CustomList.h"
#include "CustomList.cpp"

template <typename T> 
class CustomStack {
public:

    //Добавляет элемент
    void Push(const T& value) { list.PushBack(value); }
    
    //Удаляет верхний элемент
    void Pop() { if (!list.Empty()) list.PopBack(); }
    
    //Возвращает верхний элемент
    T& Top() { return list.Back(); }

    //Проверка на пустоту
    bool Empty() const { return list.Empty(); }

    //Возврашает размеры стэка
    size_t Size() const { return list.GetSize(); }

    //Чистит стэк
    void Clear() { list.Clear(); }

    //Выводит стэк
    void Print() const { list.Print(); }

private:
    CustomList<T> list; 
};