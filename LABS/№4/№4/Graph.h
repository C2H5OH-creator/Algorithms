#pragma once

#include "AdjacencyMatrix.h"

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>


class Graph
{
public:

    Graph() = default;
    Graph(const std::string& input_conf_file_name) { loadFromFile(input_conf_file_name); };

    //Чтение графа из файла
    void loadFromFile(const std::string& filename);

    //Метод для вывода графа
    void printGraph() const;

    //Создание .dot файла графа
    void createDotFile(const std::string& dotFile) const;

    //Рендеринг графа
    void renderGraph(const std::string& dotFile,
        const std::string& outputFile);

private:
	std::map<int, std::string> names;
	AdjacencyMatrix matrix;
};