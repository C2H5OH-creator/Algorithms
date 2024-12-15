#include "AdjacencyMatrix.h"

void AdjacencyMatrix::setValue(size_t row, size_t col, int value) {
    if (row >= matrix.size() || col >= matrix.size()) {
        throw std::out_of_range("Вы вышли за границы матрицы смежности!");
    }
    matrix[row][col] = value;
}

int AdjacencyMatrix::getValue(size_t row, size_t col) const{
    if (row >= matrix.size() || col >= matrix.size()) {
        throw std::out_of_range("Вы вышли за границы матрицы смежности!");
    }
    return matrix[row][col];
}

void AdjacencyMatrix::resize(size_t size) {
    matrix.assign(size, std::vector<int>(size, 0));
}

// Вывод матрицы в консоль
void AdjacencyMatrix::print() const {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
}