#pragma once

#include <iostream>
#include <queue>
#include "Visualization.h"

class BinaryTree
{
protected:
    //Элемент дерева
    struct Node
    {
        int data;
        std::string name;
        Node* right;
        Node* left;
        int height;

        Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; //Корень

private:

    void clear(Node* node);
    Node* parseSubtree(const std::string& str, int& index); 

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(root); }

    virtual void add(int value) ;
    void print() const;

    //Прямой обход в глубину
    void preOrderTraversal() { preOrderTraversal(root); }
    void preOrderTraversal(Node* node);

    //Центральный обход в глубину
    void inOrderTraversal() { inOrderTraversal(root); }
    void inOrderTraversal(Node* node);
  
    //Обратный обход в глубину
    void postOrderTraversal() { postOrderTraversal(root); }
    void postOrderTraversal(Node* node);

    void visualizeBreadthFirstGrid(const std::string& dotFile, const std::string& outputFile, int maxWidth);
    
    //Отрисовка дерева
    void visualizeTree(const std::string& dotFile, const std::string& outputFile);  
    
    //Отрисовка ноды
    void visualizeNode(std::ofstream& file, Node* node, const std::string& nodeName, int& counter);

    //Парсинг скобочной записи и отрисовка
    void parseAndVisualize(const std::string& dotFile, const std::string& outputFile, const std::string& str);

    //Парсинг скобочной записи
    Node* parseTree(const std::string& str) {
        int index = 0;
        return parseSubtree(str, index);
    }
};
