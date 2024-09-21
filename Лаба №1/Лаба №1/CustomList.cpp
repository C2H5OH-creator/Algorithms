#include "CustomList.h"

void CustomList::PushFront(const long double& value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        // Обновляем индексы всех элементов
        Node* current = head->next;
        while (current != nullptr) {
            current->index++;
            current = current->next;
        }
    }
    head->index = 0;
    size++;
}

void CustomList::PushBack(const long double& value) {
    Node* newNode = new Node(value);

    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->index = 0;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->index = size;
        tail = newNode;
    }
    size++;
}

void CustomList::PopFront() {};

void CustomList::PopBack() {};

void CustomList::Clear() {
    while (tail) {
        Node* t_current = tail->prev;
        delete tail;
        tail = t_current;
        size--;
    }
};

void CustomList::Print() const {
    Node* current = head;
    bool first = true;
    std::cout << "[";
    for (size_t i = 0; i < size; i++, current = current->next){
        if (first) { std::cout << " " << current->data; first = false; }
        else std::cout << ", " << current->data;
    }
    std::cout << " ]" << std::endl;
};