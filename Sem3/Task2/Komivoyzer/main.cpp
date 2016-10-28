#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <cmath>

using std::vector;
using std::cout;
using std::cin;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::stack;

#define PI_ 3.14159265358979323846
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
    void union_vert(int vert_a, int vert_b) {
        vert_a = find_root(vert_a);
        vert_b = find_root(vert_b);
        if (vert_a != vert_b) {
            if (rang_[vert_a] > rang_[vert_b]) {
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
    Edge(int first_vert, int second_vert, float length) {
        first_vert_ = first_vert;
        second_vert_ = second_vert;
        length_ = length;
    }
    int first_vert_;
    int second_vert_;
    int length_;
};

// Компаратор для сортировки рёбер.
class Compare {
public:
    bool operator()(Edge a, Edge b) {
        return a.length_ < b.length_;
    }
};

// Случайное число из диапазона.
double Random(double min, double max)
{
    return (double)(rand())/RAND_MAX*(max - min) + min;
}

pair<float, float> MakeVert(int i){
    // Две независимые случайные величины.
    float r = Random(0, 1);
    float f = Random(0, 1);
    // Получаем из них нормальное распределение точек на плоскости.
    float rand_x = cos(2 * PI_ * f) * sqrt(- 2 * log(r));
    float rand_y = sin(2 * PI_ * f) * sqrt(- 2 * log(r));
    return pair<float, float>(rand_x, rand_y);
};

// Метрика - евклидова.
float Metric(pair<float, float> a, pair<float, float> b){
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

// Хэш для пар.
struct Hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

// Класс для точного решения.
class Presize {
public:
    // Текущий минимум расстояния.
    float min_;
    Presize() {
        min_ = 20000000;
    }
    // Рекурсивная процедура поиска кратчайшего расстояния.
    void RecurKomiv(int n, int start, vector<char> &visited, vector<pair<float, float> > &verticles, float sum) {
        // Подсчет числа посещенных для проверки выхода из рекурсии.
        int count_visited = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                count_visited++;
            }
        }
        // Если есть еще не посещенные.
        if (count_visited != n) {
            // Перебираем все вершины.
            for (int i = 0; i < n; ++i) {
                if (visited[i] == 0) {
                    vector<char> tmp(visited);
                    tmp[i] = 1;
                    float tmp_sum = sum + Metric(verticles[i], verticles[start]);
                    RecurKomiv(n, i, tmp, verticles, tmp_sum);
                }
            }
        } else {
            if (min_ > sum) {
                min_ = sum;
            }
        }
    }
};
int main() {
    srand(time(0));
    // Среднеквадратичная ошибка.
    int sum_dev = 0;
    // Число вершин.
    float vert_count = 10;
    // Число независмых запусков эксперимента.
    int exper_count = 10;
    for (int t = 0; t < exper_count; ++t) {
        int edge_count = vert_count * (vert_count - 1) / 2;
        // Вектор, в котором хранятся ребра.
        vector<Edge> edges;
        // Вектор, в котором хранятся вершины.
        vector< pair<float, float> > verticles;
        // Хэш для определения номера вершины.
        unordered_map< pair<float, float>, int, Hash > number;
        // Заполнение вектора вершин.
        for (int i = 0; i < vert_count; ++i) {
            pair<float, float> tmp_vert = MakeVert(i);
            verticles.push_back(pair<float, float>(tmp_vert));
            // Номера вершин начинается с 1.
            number.insert(pair< pair<float, float>, int >(tmp_vert, i + 1));
        }

        // Заполнение вектора ребер.
        for (int i = 0; i < vert_count - 1; ++i) {
            for (int j = i + 1; j < vert_count; ++j) {
                Edge tmp_edge(i + 1, j + 1, Metric(verticles[i], verticles[j]));
                edges.push_back(tmp_edge);
            }
        }
        Compare comparator;
        std::sort(edges.begin(), edges.end(), comparator);
        DSU dsu(vert_count);
        // Вектор остаточного дерева.
        vector<Edge> span_tree;
        int sum = 0;
        // Проходим по отсортированному вектору рёбер
        // и добавляем в случае необходимости текущее ребро
        for (int j = 0; j < edge_count; ++j) {
            int vert_a = edges[j].first_vert_;
            int vert_b = edges[j].second_vert_;
            int length  = edges[j].length_;
            if (dsu.find_root(vert_a) != dsu.find_root(vert_b)) {
                dsu.union_vert(vert_a, vert_b);
                span_tree.push_back(edges[j]);
                sum++;
            }
        }
        int span_count = 0;
        // Удвоение ребер.
        for (int i = 0; i < sum; ++i) {
            span_tree.push_back(span_tree[i]);
            span_count++;
        }
        // Поиск эйлерова цикла.
        vector<int> eler;
        stack<int> vert_stack;
        vert_stack.push(1);
        while (!vert_stack.empty()) {
            int curr_vert = vert_stack.top();
            // Поиск соседней вершины.
            for (auto it = span_tree.begin(); it != span_tree.end(); ++it) {
                if (it->first_vert_ == curr_vert) {
                    vert_stack.push(it->second_vert_);
                    span_tree.erase(it);
                    break;
                }
                if (it->second_vert_ == curr_vert) {
                    vert_stack.push(it->first_vert_);
                    span_tree.erase(it);
                    break;
                }
            }
            // Если нет непросмотренных соседей.
            if (curr_vert == vert_stack.top()) {
                vert_stack.pop();
                eler.push_back(curr_vert);
            }
        }
        // Построение Гамильтонова цикла.
        vector<int> result;
        for (auto it = eler.begin(); it != eler.end(); ++it) {
            char flag = 0;
            for (auto it1 = result.begin(); it1 != result.end(); ++it1) {
                if (*it1 == *it) {
                    flag = 1;
                }
            }
            if (!flag) {
                result.push_back(*it);
            }
        }
        // Подсчет расстояния.
        float dist = 0;
        for (auto it = result.begin(); it != result.end(); ++it) {
            auto tmp_it = it;
            tmp_it++;
            dist += Metric(verticles[*it - 1], verticles[*tmp_it - 1]);
        }
        dist += Metric(verticles[*result.begin()], verticles[*(result.end()--)]);

        // Точное решение.
        vector<char> visited(vert_count, 0);
        Presize pr;
        pr.RecurKomiv(vert_count, 0, visited, verticles, 0);
        cout << pr.min_ << ' ' << dist << '\n' ;
        sum_dev += (dist - pr.min_) * (dist - pr.min_);
    }
    cout << sqrt(sum_dev / exper_count);

    return 0;
}