
#include <iostream>
#include "Visualization.h"

int main() {
    Visualization visuo;
    int depth = 3; // Задайте глубину дерева
    std::string nodeLabel = "Узел"; // Задайте шаблон имени для узлов
    std::string internalColor = "lightblue"; // Задайте цвет для внутренних узлов
    std::string leafColor = "lightgreen"; // Задайте цвет для листьев дерева (салатовый)

    std::string dotFile = "binary_tree.dot";
    std::string outputFile = "Бинарное_дерево.png";

    // Создание DOT файла с цветами
    visuo.createDotFile(dotFile, depth, nodeLabel, internalColor, leafColor);

    // Рендеринг графа в изображение
    visuo.renderGraph(dotFile, outputFile);

    return 0;
}
