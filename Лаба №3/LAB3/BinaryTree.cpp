#include "BinaryTree.h"

    //Очистка дерева
    void BinaryTree::clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    // Добавить узел в дерево
    void BinaryTree::add(int value) {
        if (!root) {
            root = new Node(value);
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (!current->left) {
                current->left = new Node(value);
                return;
            }
            else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = new Node(value);
                return;
            }
            else {
                q.push(current->right);
            }
        }
    }

    //Обход в ширину
    void BinaryTree::print() const {
        if (!root) {
            std::cout << "Дерево пусто.\n";
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            std::cout << "Элемент: " << current->data << std::endl;

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << "\n";
    }

    //Отрисовка обхода
    void BinaryTree::visualizeBreadthFirstGrid(const std::string& dotFile, const std::string& outputFile, int maxWidth) {
        if (!root) {
            std::cerr << "Дерево пусто, визуализация невозможна.\n";
            return;
        }

        Visualization viz;
        std::ofstream file(dotFile);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << dotFile << "\n";
            return;
        }

        file << "digraph Grid {\n";
        file << "    node [style=filled, fontcolor=black, color=black];\n";
        file << "    rankdir=LR;\n"; // Устанавливаем направление для графа

        std::queue<Node*> q;
        q.push(root);

        int counter = 1;                // Счетчик узлов
        int column = 0;                 // Текущая ширина строки
        bool reverse = false;           // Флаг направления (прямое/обратное)
        std::vector<std::string> row;   // Узлы текущей строки
        std::vector<std::string> prevRow; // Узлы предыдущей строки

        // Добавляем корень в граф
        std::string lastNode = "Node_" + std::to_string(counter);
        file << "    " << lastNode << " [label=\"" << root->data << "\", fillcolor=\"lightblue\"];\n";
        row.push_back(lastNode);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left) {
                std::string childName = "Node_" + std::to_string(++counter);
                file << "    " << childName << " [label=\"" << current->left->data << "\", fillcolor=\"lightblue\"];\n";
                q.push(current->left);
                row.push_back(childName);
            }

            if (current->right) {
                std::string childName = "Node_" + std::to_string(++counter);
                file << "    " << childName << " [label=\"" << current->right->data << "\", fillcolor=\"lightblue\"];\n";
                q.push(current->right);
                row.push_back(childName);
            }

            // Проверяем, достигнута ли ширина строки
            if (row.size() == maxWidth || q.empty()) {
                // Соединяем узлы в текущей строке
                if (reverse) {
                    for (size_t i = row.size(); i > 1; --i) {
                        file << "    " << row[i - 1] << " -> " << row[i - 2] << ";\n";
                    }
                }
                else {
                    for (size_t i = 0; i < row.size() - 1; ++i) {
                        file << "    " << row[i] << " -> " << row[i + 1] << ";\n";
                    }
                }

                // Соединяем предыдущую строку с текущей (если существует)
                if (!prevRow.empty()) {
                    if (reverse) {
                        file << "    " << prevRow.front() << " -> " << row.back() << ";\n";
                    }
                    else {
                        file << "    " << prevRow.back() << " -> " << row.front() << ";\n";
                    }
                }

                // Сохраняем текущую строку как предыдущую, переключаем направление
                prevRow = row;
                row.clear();
                reverse = !reverse;
            }
        }

        file << "}\n";
        file.close();

        // Генерация изображения
        viz.renderGraph(dotFile, outputFile);
    }

    //Отрисовка всего дерева
    void BinaryTree::visualizeTree(const std::string& dotFile, const std::string& outputFile) {
        Visualization viz;
        std::ofstream file(dotFile);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << dotFile << "\n";
            return;
        }

        file << "digraph Tree {\n";
        file << "    node [style=filled, fontcolor=black, color=black];\n";


        int counter = 1; // Счётчик для узлов
        if (root) {
            visualizeNode(file, root, "Node_" + std::to_string(counter++), counter);
        }

        file << "}\n";
        file.close();

        // Генерация изображения
        viz.renderGraph(dotFile, outputFile);
    }

    //Отрисовка ноды
    void BinaryTree::visualizeNode(std::ofstream& file, Node* node, const std::string& nodeName, int& counter) {
        file << "    " << nodeName << " [label=\"" << node->data << "\", fillcolor=\"lightblue\"];\n";

        if (node->left) {
            std::string leftName = "Node_" + std::to_string(counter++);
            file << "    " << nodeName << " -> " << leftName << ";\n";
            visualizeNode(file, node->left, leftName, counter);
        }

        if (node->right) {
            std::string rightName = "Node_" + std::to_string(counter++);
            file << "    " << nodeName << " -> " << rightName << ";\n";
            visualizeNode(file, node->right, rightName, counter);
        }
    }
    
    //Парсинг подстроки для скобочной записи
    BinaryTree::Node* BinaryTree::parseSubtree(const std::string& str, int& index) {
        for (; index < str.length(); ++index) {
            char currentChar = str[index];

            // Пропускаем возможные пробелы
            if (currentChar == ' ') {
                continue;
            }

            if (currentChar == '(') {
                index++;

                while (index < str.length() && str[index] == ' ') {
                    ++index;
                }

                if (index + 4 < str.length() && str.substr(index, 4) == "null") {
                    index += 4; // Пропускаем "null"
                    return nullptr;
                }

                // Читаем значение узла
                int value = 0;
                while (index < str.length() && std::isdigit(str[index])) {
                    value = value * 10 + (str[index] - '0');
                    ++index;
                }

                Node* node = new Node(value); 
               
                while (index < str.length() && str[index] == ' ') {
                    ++index;
                }

                if (index < str.length() && str[index] == '(') {
                    node->left = parseSubtree(str, index);
                }

                while (index < str.length() && str[index] == ' ') {
                    ++index;
                }

                if (index < str.length() && str[index] == '(') {
                    node->right = parseSubtree(str, index);
                }

                while (index < str.length() && str[index] == ' ') {
                    ++index;
                }

                if (index < str.length() && str[index] == ')') {
                    ++index;
                }
                else {
                    std::cerr << "Ошибка: Ожидалась закрывающая скобка ')' по индексу " << index << std::endl;
                    return nullptr;
                }

                return node;
            }

            // Проверяем наличие некорректных символов
            if (!std::isdigit(currentChar) && currentChar != ' ' && currentChar != '(' && currentChar != ')') {
                std::cerr << "Ошибка: Неизвестный символ'" << currentChar << "' по индексу " << index << std::endl;
                return nullptr;
            }
        }

        return nullptr; // Возвращаем nullptr, если узел не найден
    }
    
    //Чтение из файла и отрисовка
    void BinaryTree::parseAndVisualize(const std::string& dotFile, const std::string& outputFile, const std::string& str) {
        // Парсим строку и строим дерево
        root = parseTree(str);

        // Если дерево успешно построено, визуализируем его
        if (root) {
            visualizeTree(dotFile, outputFile);
        }
        else {
            std::cerr << "Ошибка: дерево не было построено." << std::endl;
        }
    }

    //Прямой обход в глубину
    void BinaryTree::preOrderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        // Посещаем текущий узел
        std::cout << "Элемент: " << node->data << std::endl;

        // Рекурсивно посещаем левое поддерево
        preOrderTraversal(node->left);

        // Рекурсивно посещаем правое поддерево
        preOrderTraversal(node->right);
    }

    void BinaryTree::postOrderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << "Элемент: " << node->data << std::endl;
    }
    
    void BinaryTree::inOrderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        inOrderTraversal(node->left);
        std::cout << "Элемент: " << node->data << std::endl;
        inOrderTraversal(node->right);
    }