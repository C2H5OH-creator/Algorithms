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

// Функция для создания .dot файла (неориентированный граф)
void Graph::createDotFile(const std::string& fileName) const {

    std::string dotFile = fileName + ".dot";

    std::ofstream file(dotFile);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + dotFile);
    }

    file << "graph G {\n"; // Начало графа (неориентированный граф)

    // Добавляем вершины
    for (std::map<int, std::string>::const_iterator it = names.begin(); it != names.end(); ++it) {
        file << "  \"" << it->second << "\";\n";
    }

    // Добавляем рёбра с весами
    for (int i = 0; i < names.size(); ++i) {
        for (int j = i + 1; j < names.size(); ++j) {
            int weight = matrix.getValue(i, j);
            if (weight > 0) {  // Если есть ребро (вес > 0)
                file << "  \"" << names.at(i) << "\" -- \"" << names.at(j) << "\" [label=\"" << weight << "\"];\n";
            }
        }
    }

    file << "}\n";  // Конец графа

    std::cout << "DOT-файл создан: " << dotFile << "\n";
}

// Функция для создания .dot файла для MST
void Graph::createMSTDotFile(const std::string& fileName) {

    std::string dotFile = fileName + ".dot";

    // Выполняем алгоритм Краскала для получения рёбер MST
    std::vector<UnionFind::Edge> mstEdges = kruskal();

    std::ofstream file(dotFile);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + dotFile);
    }

    file << "graph MST {\n"; // Начало графа (неориентированный граф)

    // Добавляем вершины
    for (std::map<int, std::string>::const_iterator it = names.begin(); it != names.end(); ++it) {
        file << "  \"" << it->second << "\";\n";
    }


    // Добавляем рёбра MST с весами
    for (const auto& edge : mstEdges) {
        file << "  \"" << names.at(edge.u) << "\" -- \"" << names.at(edge.v)
            << "\" [label=\"" << edge.weight << "\"];\n";
    }

    file << "}\n"; // Конец графа

    std::cout << "MST-DOT-файл создан: " << dotFile << "\n";
}

// Функция для рендеринга графа в изображение
void Graph::renderGraph(const std::string& filesName, const std::string& outputFileExtention) {
    std::string dotFile = filesName + ".dot";
    std::string outputFile = filesName + "." + outputFileExtention;
    
    std::string command = "dot -Tsvg " + dotFile + " -o " + outputFile;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Ошибка: не удалось выполнить команду Graphviz\n";
    }
    else {
        std::cout << "Граф сохранён в " << outputFile << "\n";
    }
}

// Добавление метода для извлечения рёбер из графа
std::vector<UnionFind::Edge> Graph::getEdges() const {
    std::vector<UnionFind::Edge> edges;

    // Проходим по всем элементам матрицы смежности
    for (size_t i = 0; i < matrix.getSize(); i++) {
        for (size_t j = i + 1; j < matrix.getSize(); j++) { // Только верхняя треугольная часть
            int weight = matrix.getValue(i, j);
            if (weight > 0) {
                edges.emplace_back(i, j, weight); // Добавляем ребро (u, v, вес)
            }
        }
    }
    return edges;
}

// Алгоритм Краскала
std::vector<UnionFind::Edge> Graph::kruskal() {

    // Получаем все рёбра графа
    std::vector<UnionFind::Edge> edges = Graph::getEdges();

    // Сортируем рёбра по возрастанию веса
    std::sort(edges.begin(), edges.end(), UnionFind::compareEdges);

    // Инициализируем Union-Find
    UnionFind uf(matrix.getSize());

    std::vector<UnionFind::Edge> mst; // Результирующее минимальное остовное дерево

    for (const UnionFind::Edge& edge : edges) {
        // Если вершины не принадлежат одному множеству, добавляем ребро
        if (uf.find(edge.u) != uf.find(edge.v)) {
            mst.push_back(edge);
            uf.unite(edge.u, edge.v);
        }

        // Если количество рёбер в дереве равно n-1, завершаем
        if (mst.size() == matrix.getSize() - 1) {
            break;
        }
    }

    return mst;
}

// Обход в ширину
void Graph::bfs(size_t start) {
    size_t size = matrix.getSize();

    if (start >= size) {
        throw std::out_of_range("Начальная вершина выходит за пределы графа");
    }

    std::vector<bool> visited(size, false); // Массив посещённых вершин
    std::queue<size_t> q; // Очередь для BFS

    visited[start] = true; // Отмечаем начальную вершину как посещённую
    q.push(start); // Добавляем её в очередь

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();

        std::cout << "Посещена вершина: " << current << std::endl;

        // Обходим соседей текущей вершины
        for (size_t neighbor = 0; neighbor < size; ++neighbor) {
            if (matrix.getValue(current, neighbor) != 0 && !visited[neighbor]) {
                visited[neighbor] = true; // Помечаем вершину как посещённую
                q.push(neighbor); // Добавляем её в очередь
            }
        }
    }
}

// Обход в глубину
void Graph::dfsRecursive(size_t current, std::vector<bool>& visited) {
    // Пометить текущую вершину как посещённую
    visited[current] = true;
    std::cout << "Посещена вершина: " << current << std::endl;

    // Рекурсивно посещаем соседей
    for (size_t neighbor = 0; neighbor < matrix.getSize(); ++neighbor) {
        if (matrix.getValue(current, neighbor) != 0 && !visited[neighbor]) {
            dfsRecursive(neighbor, visited);
        }
    }
}

void Graph::dfs(size_t start) {
    size_t size = matrix.getSize();

    if (start >= size) {
        throw std::out_of_range("Начальная вершина выходит за пределы графа");
    }

    std::vector<bool> visited(size, false); // Массив посещённых вершин
    dfsRecursive(start, visited);
}