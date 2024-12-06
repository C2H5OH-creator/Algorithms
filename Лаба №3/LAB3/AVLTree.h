#pragma once
#include "BinaryTree.h"

class AVLTree : public BinaryTree
{
private:
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* a) {
        Node* b = a->left;
        Node* C = b->right;

        b->right = a;
        a->left = C;

        a->height = std::max(getHeight(a->left), getHeight(a->right)) + 1;
        b->height = std::max(getHeight(b->left), getHeight(b->right)) + 1;

        return b;
    }

    Node* leftRotate(Node* b) {
        Node* a = b->right;
        Node* C = a->left;

        a->left = b;
        b->right = C;

        b->height = std::max(getHeight(b->left), getHeight(b->right)) + 1;
        a->height = std::max(getHeight(a->left), getHeight(a->right)) + 1;

        return a;
    }

    Node* leftRightRotate(Node* node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    Node* rightLeftRotate(Node* node) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            return node; // Дубликаты не добавляются
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && value > node->left->data) {
            return leftRightRotate(node);
        }

        if (balance < -1 && value < node->right->data) {
            return rightLeftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        }
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }

        if (balance > 1 && getBalance(root->left) < 0) {
            return leftRightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            return rightLeftRotate(root);
        }

        return root;
    }

public:
    void add(int value) override {
        root = insert(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

};

