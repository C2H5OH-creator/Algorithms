#pragma once
#include <iostream>

template <typename T>
class CustomList{
public:
    CustomList() : head(nullptr), tail(nullptr), size(0) {};
    ~CustomList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    };

    // Операции с элементами списка
    void PushFront(const T& value);
    void PushBack(const T& value);
    void PopFront();
    void PopBack();

    T& Front() const { return head->data; };
    T& Back() const { return tail->data; };

    T& GetValue(unsigned t_index) const {
        Node* t_head = head;
        for (size_t i = 0; i < size; i++, t_head = t_head->next) {
            if (t_head->index == t_index) return t_head->data;
        }
    };

    bool Empty() const { return size == 0; };
    size_t GetSize() const { return size; };

    void Clear();

    // Вспомогательные методы
    void Print() const;

private:
    struct Node {
        T data;
        size_t index;
        Node* next;
        Node* prev;

        Node(const T& data, Node* prev = nullptr, Node* next = nullptr, size_t index = 0)
            : data(data), prev(prev), next(next), index(index) {}
    };

    Node* head;
    Node* tail;
    size_t size;
};