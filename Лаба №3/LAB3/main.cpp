
#include <iostream>
#include "BinaryTree.h"
#include "AVLTree.h"

//Чтение из файла
std::string readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return "";
    }

    std::string string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return string;
}

int main() {
    AVLTree tree;
    std::string str_input = readFromFile("Скобочная_запись.txt");

    tree.parseAndVisualize("АВЛ_дерево.dot", "АВЛ_дерево.svg", str_input);

    tree.remove(25);
    tree.visualizeTree("АВЛ_дерево.dot", "АВЛ_дерево.svg");

    //Обход в ширину
    std::cout << std::endl << "Обход в ширину" << std::endl;
    tree.print();
    
    //Прямой обход в глубину
    std::cout << std::endl << "Прямой обход в глубину" << std::endl;
    tree.preOrderTraversal();
    
    //Центральный обход в глубину
    std::cout << std::endl << "Центральный обход в глубину" << std::endl;
    tree.inOrderTraversal();
    
    //Обратный обход в глубину
    std::cout << std::endl << "Обратный обход в глубину" << std::endl;
    tree.postOrderTraversal();
   
}
