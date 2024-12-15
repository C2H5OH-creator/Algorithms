#include <iostream>

#include "Graph.h"

int main() {
	Graph graph("graph_input_file.txt");
	graph.printGraph();

	graph.createDotFile("test_file.dot");
	graph.renderGraph("test_file.dot", "test_file.svg");
	
}