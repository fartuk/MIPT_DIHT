// Задача D. Алгоритм Крускала
// Имя входного файла: kruskal.in
//        Имя выходного файла: kruskal.out
//        Ограничение по времени: 2 секунды
//        Ограничение по памяти: 64 мегабайта
//        Требуется найти в связном графе остовное дерево минимального веса.
// Формат входного файла
//        Первая строка входного файла содержит два натуральных числа 𝑛 и 𝑚 — количество вершин
//        и ребер графа соответственно (1 6 𝑛 6 20000, 0 6 𝑚 6 100000). Следующие 𝑚 строк содержат
//        описание ребер по одному на строке. Ребро номер 𝑖 описывается тремя натуральными числами
//        𝑏𝑖 𝑒𝑖 и 𝑤𝑖 — номера концов ребра и его вес соответственно
// Граф является связным.
// Формат выходного файла
//        Выведите единственное целое число - вес минимального остовного дерева.

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using std::vector;
using std::cout;
using std::cin;

// Система непересекающихся множеств.
class DSU {
public:
    vector<int> parent_;
    vector<int> rang_;
    // Конструктор от числа элементов в множествах.
    DSU(int count){
        for (int i = 0; i < count + 1; ++i) {
            parent_.push_back(i);
            rang_.push_back(1);
        }
    };
    // Корень говорит о том, в каком подмножестве лежит вершина.
    int find_root(int vert_to_find){
        if (parent_[vert_to_find] == vert_to_find){
            return vert_to_find;
        } else {
            // Сворачиваем часть путей при раскручивании стека.
            return parent_[vert_to_find] = find_root(parent_[vert_to_find]);
        }
    }
    // Слияние двух подмножеств в одно
    void union_vert(int vert_a, int vert_b){
        vert_a = find_root(vert_a);
        vert_b = find_root(vert_b);
        if (vert_a != vert_b) {
            if (rang_[vert_a] > rang_[vert_b]){
                parent_[vert_b] = vert_a;
                rang_[vert_a] = rang_[vert_a] + rang_[vert_b];
            } else{
                parent_[vert_b] = vert_a;
                rang_[vert_b] = rang_[vert_b] + rang_[vert_a];
            }
        }
    }
};

// Ребро.
class Edge {
public:
    // Конструктор.
    Edge(int first_vert,int second_vert, int length) {
        first_vert_ = first_vert;
        second_vert_ = second_vert;
        length_ = length;
    }
    int first_vert_;
    int second_vert_;
    int length_;
};

// Компаратор для сортировки Рёбер.
class Compare {
public:
    bool operator()(Edge a, Edge b) {
        return a.length_ < b.length_;
    }
};

int main() {
    std::ifstream fin("kruskal.in");
    std::ofstream fout("kruskal.out");
    int vert_count = 0;
    int edge_count = 0;
    // Ввод параметров графа.
    fin >> vert_count >> edge_count;
    // Вектор, в котором хранятся ребра.
    vector<Edge> edges;
    // Заполнение вектора рёбер.
    for (int i = 0; i < edge_count; ++i) {
        int tmp_first_vert = 0;
        int tmp_second_vert = 0;
        int tmp_length = 0;
        fin >> tmp_first_vert >> tmp_second_vert >> tmp_length;
        Edge tmp_edge(tmp_first_vert, tmp_second_vert, tmp_length);
        edges.push_back(tmp_edge);
    }
    Compare comparator;
    std::sort(edges.begin(), edges.end(), comparator);
    DSU dsu(vert_count);
    int sum = 0;
    // Проходим по отсортированному вектору рёбер
    // и добавляем в случае необходимости текущее ребро
    for (int j = 0; j < edge_count; ++j) {
        int vert_a = edges[j].first_vert_;
        int vert_b = edges[j].second_vert_;
        int length  = edges[j].length_;
        if (dsu.find_root(vert_a) != dsu.find_root(vert_b)) {
            dsu.union_vert(vert_a, vert_b);
            sum += length;
        }
    }
    fout << sum;
    return 0;
}