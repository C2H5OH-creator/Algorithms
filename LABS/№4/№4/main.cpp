#include <iostream>
#include "Graph.h"

int main() {
	Graph graph("graph_input_file2.txt");
	graph.printGraph();
    graph.createDotFile("common_graph");
	graph.renderGraph("common_graph");
    
    // Выполняем алгоритм Краскала
    std::vector<UnionFind::Edge> mst = graph.kruskal();

    graph.createMSTDotFile("MST");
    graph.renderGraph("MST");

    ///*
    // Выводим минимальное остовное дерево
    std::cout << "Минимальное остовное дерево:\n";
    for (const auto& edge : mst) {
        std::cout << "Ребро: " << graph.getName(edge.u) << " - " << graph.getName(edge.v)
            << " (Вес: " << edge.weight << ")\n";
    }
    //*/

}