#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

#include "AdjacencyMatrix.h"

class IncidenceMatrix {
public:
    // Конструкторы
    IncidenceMatrix() = default;
    IncidenceMatrix(size_t vertexCount, size_t edgeCount)
        : matrix(vertexCount, std::vector<int>(edgeCount, 0)) {
    }

    // Установка инцидентности вершины и ребра
    void setValue(size_t vertex, size_t edge, int value) {
        if (vertex >= matrix.size() || edge >= matrix[0].size()) {
            throw std::out_of_range("Index out of bounds");
        }
        matrix[vertex][edge] = value;
    }

    // Получение значения инцидентности
    int getValue(size_t vertex, size_t edge) const {
        if (vertex >= matrix.size() || edge >= matrix[0].size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[vertex][edge];
    }

    size_t getVertexCount() const { return matrix.size(); }
    size_t getEdgeCount() const { return matrix[0].size(); }

    // Изменение размера матрицы
    void resize(size_t vertexCount, size_t edgeCount) {
        matrix.resize(vertexCount);
        for (auto& row : matrix) {
            row.resize(edgeCount, 0);
        }
    }

    // Вывод матрицы в консоль
    void print() const {
        for (const auto& row : matrix) {
            for (int value : row) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }
    }

    // Преобразование из матрицы смежности
    static IncidenceMatrix fromAdjacencyMatrix(const AdjacencyMatrix& adjacencyMatrix) {
        size_t vertexCount = adjacencyMatrix.getSize();
        std::vector<std::pair<size_t, size_t>> edges;

        // Собираем все рёбра
        for (size_t i = 0; i < vertexCount; ++i) {
            for (size_t j = i; j < vertexCount; ++j) { // Проходим только верхний треугольник для неориентированного графа
                int weight = adjacencyMatrix.getValue(i, j);
                if (weight != 0) {
                    edges.emplace_back(i, j);
                }
            }
        }

        // Создаём матрицу инцидентности
        IncidenceMatrix incidenceMatrix(vertexCount, edges.size());
        for (size_t edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex) {
            size_t u = edges[edgeIndex].first;
            size_t v = edges[edgeIndex].second;

            // Устанавливаем значения для неориентированного графа
            incidenceMatrix.setValue(u, edgeIndex, 1);
            if (u != v) {
                incidenceMatrix.setValue(v, edgeIndex, 1);
            }
        }

        return incidenceMatrix;
    }

private:
    // Матрица инцидентности
    std::vector<std::vector<int>> matrix;
};
