#include "Visualization.h"

// Рекурсивная функция для создания дерева с цветами
void Visualization::createBinaryTreeDot(std::ofstream& file, const std::string& parentName, int depth, const std::string& nodeLabel, int& counter, const std::string& internalColor, const std::string& leafColor) {
    if (depth == 0) return;

    // Генерация уникального имени для текущего узла
    std::string currentNode = nodeLabel + std::to_string(counter++);

    // Если узел является листом (глубина 1), меняем цвет на салатовый
    std::string nodeColor = (depth == 1) ? leafColor : internalColor;

    // Добавляем цвет к узлу
    file << "    " << currentNode << " [label=\"" << currentNode << "\", color=\"" << nodeColor << "\", style=filled, fillcolor=\"" << nodeColor << "\"];\n";

    // Создаём связи с родительским узлом
    file << "    " << parentName << " -> " << currentNode << ";\n";

    // Рекурсивно создаём левое и правое поддерево
    if (depth > 1) {
        // Создаем левое и правое поддерево
        createBinaryTreeDot(file, currentNode, depth - 1, nodeLabel, counter, internalColor, leafColor);  // левый потомок
        createBinaryTreeDot(file, currentNode, depth - 1, nodeLabel, counter, internalColor, leafColor);  // правый потомок
    }
}

// Функция для создания DOT файла с цветами
void Visualization::createDotFile(const std::string& filename, int depth, const std::string& nodeLabel, const std::string& internalColor, const std::string& leafColor) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << filename << "\n";
        return;
    }

    file << "digraph Tree {\n";

    int counter = 1; // Счётчик для генерации уникальных имен узлов
    std::string rootNode = nodeLabel + std::to_string(counter++);

    // Добавляем цвет к корню
    file << "    " << rootNode << " [label=\"" << rootNode << "\", color=\"" << internalColor << "\", style=filled, fillcolor=\"" << internalColor << "\"];\n";

    // Рекурсивно создаём дерево начиная с корня
    createBinaryTreeDot(file, rootNode, depth, nodeLabel, counter, internalColor, leafColor);

    file << "}\n";
    file.close();
}

// Функция для рендеринга графа в изображение
void Visualization::renderGraph(const std::string& dotFile, const std::string& outputFile) {
    std::string command = "dot -Tpng " + dotFile + " -o " + outputFile;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Ошибка: не удалось выполнить команду Graphviz\n";
    }
    else {
        std::cout << "Граф сохранён в " << outputFile << "\n";
    }
}