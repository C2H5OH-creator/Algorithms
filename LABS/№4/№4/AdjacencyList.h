#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <unordered_map>

class AdjacencyList {
public:
    // Конструктор по количеству вершин
    AdjacencyList(size_t numVertices) : adjacencyList(numVertices) {}

    // Добавить ребро (для ориентированного графа)
    void addEdge(size_t from, size_t to, int weight = 1) {
        checkVertex(from);
        checkVertex(to);
        adjacencyList[from].emplace_back(to, weight);
    }

    // Добавить ребро (для неориентированного графа)
    void addUndirectedEdge(size_t v1, size_t v2, int weight = 1) {
        addEdge(v1, v2, weight);
        addEdge(v2, v1, weight);
    }

    // Получить список смежных вершин для заданной вершины
    const std::list<std::pair<size_t, int>>& getNeighbors(size_t vertex) const {
        checkVertex(vertex);
        return adjacencyList[vertex];
    }

    // Вывести список смежности в консоль
    void print() const {
        for (size_t i = 0; i < adjacencyList.size(); ++i) {
            std::cout << i << ": ";
            for (const auto& neighbor : adjacencyList[i]) {
                std::cout << "(" << neighbor.first << ", Вес: " << neighbor.second << ") ";
            }
            std::cout << "\n";
        }
    }

    // Получить количество вершин
    size_t getNumVertices() const {
        return adjacencyList.size();
    }

private:
    // Вектор списков смежности (каждая вершина имеет список пар "сосед, вес")
    std::vector<std::list<std::pair<size_t, int>>> adjacencyList;

    // Проверка валидности вершины
    void checkVertex(size_t vertex) const {
        if (vertex >= adjacencyList.size()) {
            throw std::out_of_range("Нет такой вершины");
        }
    }
};
