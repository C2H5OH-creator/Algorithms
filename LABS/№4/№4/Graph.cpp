#include "Graph.h"

void Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // Считываем первую строку для названий узлов
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string nodeName;
        int index = 0;
        while (iss >> nodeName) {
            names[index++] = nodeName;
        }
    }

    // Размер матрицы соответствует количеству узлов
    size_t size = names.size();
    matrix.resize(size);

    // Считываем строки для заполнения матрицы смежности
    size_t row = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int weight;
        size_t col = 0;
        while (iss >> weight) {
            matrix.setValue(row, col++, weight);
        }
        ++row;
    }
}

// Метод для вывода графа
void Graph::printGraph() const {
    std::cout << "Names:\n";
    for (std::map<int, std::string>::const_iterator it = names.begin(); it != names.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }

    std::cout << "\nAdjacency Matrix:\n";
    matrix.print();
}

// Функция для создания .dot файла
void Graph::createDotFile(const std::string& dotFile) const {
    std::ofstream file(dotFile);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + dotFile);
    }

    file << "digraph G {\n"; // Начало графа (направленный граф)

    // Добавляем вершины
    for (std::map<int, std::string>::const_iterator it = names.begin(); it != names.end(); ++it) {
        file << "  \"" << it->second << "\";\n";
    }

    // Добавляем рёбра с весами
    for (int i = 0; i < names.size(); ++i) {
        for (int j = i + 1; j < names.size(); ++j) {
            int weight = matrix.getValue(i, j);
            if (weight > 0) {  // Если есть ребро (вес > 0)
                file << "  \"" << names.at(i) << "\" -> \"" << names.at(j) << "\" [label=\"" << weight << "\"];\n";
            }
        }
    }

    file << "}\n";  // Конец графа

    std::cout << "DOT file created: " << dotFile << "\n";
}

// Функция для рендеринга графа в изображение
void Graph::renderGraph(const std::string& dotFile, const std::string& outputFile) {
    std::string command = "dot -Tsvg " + dotFile + " -o " + outputFile;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Ошибка: не удалось выполнить команду Graphviz\n";
    }
    else {
        std::cout << "Граф сохранён в " << outputFile << "\n";
    }
}