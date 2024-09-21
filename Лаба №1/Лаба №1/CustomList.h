#pragma once

#include <iostream>

class CustomList {
public:
	CustomList() : head(nullptr), tail(nullptr) {};
	~CustomList() {
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	};

	// Операции с элементами списка
	void PushFront(const long double& value);
	void PushBack(const long double& value);
	void PopFront();            
	void PopBack();

	long double& Front() const { return head->data; };

	long double& Back() const { return tail->data; };

	long double& GetValue(unsigned t_index) const {
		Node* t_head = head;
		for (size_t i = 0; i < size; i++, t_head = t_head->next){
			if (t_head->index == t_index) return t_head->data;
		}
	};

	bool Empty() const {
		if (!size) {
			return true;
		}
		else return false;
	};

	size_t GetSize() const { return size; };

	void Clear();

	// Вспомогательные методы
	void Print() const;  

private:
	struct Node {
		long double data;
		size_t index;
		Node* next;
		Node* prev;

		Node(const long double& data, Node* prev = nullptr, Node* next = nullptr)
			: data(data), prev(prev), next(next) {}
	};
	Node* head;
	Node* tail;
	size_t size = 0;
};