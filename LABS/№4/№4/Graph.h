#pragma once

#include "AdjacencyMatrix.h"
#include "UnionFind.h"

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>


class Graph
{
public:

    // Конструкторы
    Graph() = default;
    Graph(const std::string& input_conf_file_name) { loadFromFile(input_conf_file_name); };

    std::string getName(int index) const {
        return names.at(index);
    }

    //Чтение графа из файла
    void loadFromFile(const std::string& filename);

    //Метод для вывода графа
    void printGraph() const;

    //Создание .dot файла графа
    void createDotFile(const std::string& dotFile) const;

    void createMSTDotFile(const std::string& dotFile) ;

    //Рендеринг графа
    void renderGraph(const std::string& filesName, const std::string& outputFileExtention = "svg");

    // Алгоритм Краскала
    std::vector<UnionFind::Edge> kruskal();

    // Обход в глубину
    void bfs(size_t start);

    //Обход в ширину
    void dfsRecursive(size_t current, std::vector<bool>& visited);

    void dfs(size_t start);

private:

    // Метод для извлечения рёбер из графа
    std::vector<UnionFind::Edge> getEdges() const;

	std::map<int, std::string> names;
	AdjacencyMatrix matrix;
};