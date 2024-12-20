#pragma once

#include <iostream>
#include <vector>

class UnionFind
{
public:

    struct Edge {
        int u, v, weight;
        Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
    };

    // Конструктор
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // Поиск элемента в множестве
    int find(int x);

    // Объединение двух множеств
    void unite(int x, int y);

    // Сортировка рёбер по весу
    static bool compareEdges(const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    }

private:
    std::vector<int> parent, rank;
};

