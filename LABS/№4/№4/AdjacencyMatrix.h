#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

class AdjacencyMatrix {
public:
    //Конструкторы
	AdjacencyMatrix() = default;
	AdjacencyMatrix(size_t size) : matrix(size, std::vector<int>(size, 0)) {};

    //Установка веса ребра
    void setValue(size_t row, size_t col, int value);
   
    //Получение веса ребра
    int getValue(size_t row, size_t col) const; 

    //Изменение размера матрицы
    void resize(size_t size);

    // Вывод матрицы в консоль
    void print() const;

private:
    //Матрица смежности
	std::vector<std::vector<int>> matrix;

};

