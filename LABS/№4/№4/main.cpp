#include <iostream>
#include "Graph.h"

int main() {
	Graph graph("graph_input_file2.txt");
    std::cout << std::endl;
	graph.printGraph();
    std::cout << std::endl;
    graph.createDotFile("common_graph");
	graph.renderGraph("common_graph");
    
    // Обход в ширину
    std::cout << std::endl << "Обход в ширину:" << std::endl;
    graph.bfs(0);

    // Обход в глубину
    std::cout << std::endl << "Обход в глубину:" << std::endl;
    graph.dfs(0);

    graph.createMSTDotFile("MST");
    graph.renderGraph("MST");
}