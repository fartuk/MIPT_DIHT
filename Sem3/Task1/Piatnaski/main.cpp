// Задача A. Восьминашки
// Имя входного файла: puzzle.in
// Имя выходного файла: puzzle.out
// Ограничение по времени: 1 секунда
// Ограничение по памяти: 256 мегабайт
// «Восьминашки» – упрощенный вариант известной головоломки «Пятнашки». Восемь костяшек,
// пронумерованных от 1 до 8, расставлены по ячейкам игровой доски 3 на 3, одна ячейка при этом
// остается пустой. За один ход разрешается передвинуть одну из костяшек, расположенных рядом с
// пустой ячейкой, на свободное место. Цель игры – для заданной начальной конфигурации игровой
// доски за минимальное число ходов получить выигрышную конфигурацию (пустая ячейка обозначена
// нулем):
// 1 2 3
// 4 5 6
// 7 8 0
// Формат входного файла
// Во входном файле содержится начальная конфигурация головоломки – 3 строки по 3 числа в
// каждой.
// Формат выходного файла
// Если решение существует, то в первой строке выходного файла выведите минимальное число
// перемещений костяшек, которое нужно сделать, чтобы достичь выигрышной конфигурации, а во
// второй строке выведите соответствующую последовательность ходов: L означает, что в результате
// перемещения костяшки пустая ячейка сдвинулась влево, R – вправо, U – вверх, D – вниз. Если таких
// последовательностей несколько, то выведите любую из них. Е*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include <math.h>
#include <limits>
#include <algorithm>
#include <fstream>

using std::vector;
using std::unordered_set;
using std::queue;
using std::cout;
using std::list;
using std::priority_queue;
using std::string;
using std::pair;


unsigned long long MyPow(unsigned long long x, unsigned long long p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    return x * MyPow(x, p - 1);
}

const int kSize = 4;

class Node {
public:
    Node& operator=(const Node& v) {
        base_ = v.get_base();
        return *this;
    }

    const unsigned long long get_base() const {
        return base_;
    }
    //создание узла из двумерного массива
    //кодирование умножением на 16 в степени
    Node(vector< vector<int> > donor_vector) {
        base_ = 0;
        for (int i = 0; i < kSize; ++i) {
            for (int j = 0; j < kSize; ++j) {
                base_ += donor_vector[i][j] * MyPow(kSize * kSize, i * kSize + j);
            }
        }
    }
    Node() {
        base_ = 0;
    }
    Node code(vector< vector<int> > donor_vector) {
        Node return_node(donor_vector);
        return return_node;
    }
    //получение двумерного массива из числа
    vector< vector<int> > decode() {
        vector< vector<int> > tmp_vector;
        unsigned long long copy_base = base_;
        for (int i = 0; i < kSize; ++i) {
            vector<int> null_vector;
            tmp_vector.push_back(null_vector);
            for (int j = 0; j < kSize; ++j) {
                tmp_vector[i].push_back(copy_base % (kSize * kSize));
                copy_base = copy_base / (kSize * kSize);
            }
        }
        return tmp_vector;
    }
    //создание соседних игровых позиций
    list< pair<Node, string> > make_nbs() {
        vector< vector<int> > tmp_vector;
        tmp_vector = this->decode();
        list< pair<Node, string> > return_list;
        //получаем позицию нуля
        int null_i = 0;
        int null_j = 0;
        int i = 0;
        int j = 0;
        for (int i = 0; i < kSize; ++i) {
            for (int j = 0; j < kSize; ++j) {
                if (tmp_vector[i][j] == 0) {
                    null_i = i;
                    null_j = j;
                }
            }
        }

        //заполняем список соседних игровых позиций
        //если не на нижней границе поля
        if (null_i != kSize - 1) {
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i + 1][null_j]);
            Node tmp_node(tmp_vector);
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i + 1][null_j]);
            return_list.push_back(pair<Node, string>(tmp_node, "D"));
        }
        //если не на верхней границе поля
        if (null_i != 0) {
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i - 1][null_j]);
            Node tmp_node(tmp_vector);
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i - 1][null_j]);
            return_list.push_back(pair<Node, string>(tmp_node, "U"));
        }
        //если не на правой границе поля
        if (null_j != kSize - 1) {
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i][null_j + 1]);
            Node tmp_node(tmp_vector);
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i][null_j + 1]);
            return_list.push_back(pair<Node, string>(tmp_node, "R"));
        }
        //если не на левой границе поля
        if (null_j != 0) {
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i][null_j - 1]);
            Node tmp_node(tmp_vector);
            std::swap(tmp_vector[null_i][null_j], tmp_vector[null_i][null_j - 1]);
            return_list.push_back(pair<Node, string>(tmp_node, "L"));
        }

        return return_list;
    }
private:
    unsigned long long base_;

};

//Получение эвристического расстояния из ноды
int Evristic(Node node) {
    vector< vector<int> > tmp_vector = node.decode();
    int sum = 0;
    for (int i = 0; i < kSize; ++i) {
        for (int j = 0; j < kSize; ++j) {
            if (i * kSize + j + 1 != tmp_vector[i][j]) {
                sum++;
            }
        }
    }
    return sum;
};
//объекты этого класса лежат в очереди
class Vert{
public:
    Vert(Node node) {
        parent_ = nullptr;
        parent_label_ = "Y";
        node_ = node;
        curr_distance_ = std::numeric_limits<int>::infinity();
        evristic_ = Evristic(node);
        sum_distance_ = curr_distance_ + evristic_;
    }
    Vert& operator=(const Vert& v) {
        node_ = v.get_node();
        parent_ = v.get_parent();
        parent_label_ = v.get_parent_label();
        sum_distance_ = v.sum_distance_;
        curr_distance_ = v.curr_distance_;
        evristic_ = v.evristic_;
        return *this;
    }
    Node get_node() const {
        return node_;
    }
    int get_sum_distance() {
        return sum_distance_;
    }
    int get_curr_distance() {
        return curr_distance_;
    }
    int get_evristic() {
        return evristic_;
    }
    Vert * get_parent()const {
        Vert* tmp = parent_;
        return tmp;
    }
    string get_parent_label()const {
        return parent_label_;
    }
    void set_curr_distance(int curr_distance) {
        curr_distance_ = curr_distance;
    }
    void set_sum_distance(int sum_distance) {
        sum_distance_ = sum_distance;
    }
    void set_parent(Vert* parent) {
        parent_ = parent;
    }
    void set_parent_label(string parent_label) {
        parent_label_ = parent_label;
    }
private:
    Vert* parent_;
    string parent_label_;
    Node node_;
    //итоговое расстояние
    int sum_distance_;
    //расстояние от начальной
    int curr_distance_;
    //эвристика до конечной
    int evristic_;
};

//сравнение элементов в очереди с приоритетом
class Compare
{
public:
    bool operator() (Vert a, Vert b) {
        return a.get_sum_distance() > b.get_sum_distance();
    }
};


pair<string, int> AStar(Node from_node, Node to) {
    Vert from(from_node);

    //очередь с приоритетом для НЕиспользованных вершин
    priority_queue<Vert, vector<Vert>, Compare> not_used;
    //хэш для быстрой проверки наличия элемента в очереди
    unordered_set<unsigned long long> not_used_in;
    //массив использованных
    list<Vert> used;
    //хэш для использованных
    unordered_set<unsigned long long> used_in;
    //вставка начальной вершины в неиспользованные
    from.set_curr_distance(0);
    not_used.push(from);
    not_used_in.insert(from.get_node().get_base());
    //пока есть элементы в очереди
    while (!not_used.empty()) {
        //берется самая приоритетная вершина из очереди неиспользованных
        Vert curr_vert = not_used.top();
        //если дошли до финальной позиции
        if (curr_vert.get_node().get_base() == to.get_base()) {
            int sum_distance = 0;
            string way = "";
            //проход по родителям и восстановление пути
            while (curr_vert.get_parent_label() != "Y") {
                way = way + curr_vert.get_parent_label();
                curr_vert = *(curr_vert.get_parent());
                sum_distance++;
            }
            std::reverse(way.begin(), way.end());
            pair<string, int> result = pair<string, int>(way, sum_distance);
            return result;
        }
        //вставка в массив родителей
        used.push_back(not_used.top());
        used_in.insert(not_used.top().get_node().get_base());
        Vert* tmp = &used.back();
        //и удаление из неиспользованных
        not_used_in.erase(not_used_in.find(not_used.top().get_node().get_base()));
        not_used.pop();

        //просмотр его соседей, полученных списком
        list< pair<Node, string> > nbs_list = curr_vert.get_node().make_nbs();
        while (!nbs_list.empty()) {
            Vert nbs_vert(nbs_list.front().first);
            int new_curr_distance = curr_vert.get_curr_distance() + 1;
            //проверка не улучшилось ли расстояние
            if (used_in.find(nbs_vert.get_node().get_base()) == used_in.end() || new_curr_distance < nbs_vert.get_curr_distance()) {
                //обновление полей
                nbs_vert.set_parent(tmp);
                nbs_vert.set_parent_label(nbs_list.front().second);
                nbs_vert.set_curr_distance(new_curr_distance);
                nbs_vert.set_sum_distance(new_curr_distance + nbs_vert.get_evristic());
                //кладем в НЕиспользованные, если его там не было
                if(not_used_in.find(nbs_vert.get_node().get_base()) == not_used_in.end()) {
                    not_used.push(nbs_vert);
                    not_used_in.insert(nbs_vert.get_node().get_base());
                }
            }
            nbs_list.pop_front();
        }
    }
    if (not_used.empty()){
        pair<string, int> result = pair<string, int>("n", -1);
        return result;

    }
}

//проверка четности перестановки
bool ParityPosition(Node node) {
    int sum = 0;
    vector< vector<int> > matrix = node.decode();
    //для каждого числа просматриваются следующие
    for (int i = 0; i < kSize; ++i) {
        for (int j = 0; j < kSize; ++j) {
            //прибавляем номер строки с пустой клеткой
            if (matrix[i][j] != 0){
                for (int k = 0; k < kSize; ++k) {
                    for (int l = 0; l < kSize; ++l) {
                        if (!(k < i || (k == i && l <= j)) && matrix[i][j] < matrix[k][l]) {
                            sum += 1;
                        }
                    }
                }
            }
        }
    }
    if (sum % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::ifstream fin("puzzle.in");
    std::ofstream fout("puzzle.out");
    //вектор, из которого будет сформировано начальное положение
    vector< vector<int> > start_vector;
    //ввод вектора
    for (int i = 0; i < kSize; ++i) {
        vector<int> tmp_vector;
        start_vector.push_back(tmp_vector);
        for (int j = 0; j < kSize; ++j) {
            int tmp_edge;
            fin >> tmp_edge;
            start_vector[i].push_back(tmp_edge);
        }
    }
    //вектор, из которого будет сформирована финальная позиция доски
    vector< vector<int> > final_vector;
    int sum = 1;
    //заполнение последовательностью от 1 до квадрата размера
    for (int i = 0; i < kSize; ++i) {
        vector<int> tmp_vector;
        final_vector.push_back(tmp_vector);
        for (int j = 0; j < kSize; ++j) {
            final_vector[i].push_back(sum);
            sum++;
        }
    }
    //пустая клетка в конце
    final_vector[kSize - 1][kSize - 1] = 0;
    //формируем ноды
    Node start_node(start_vector);
    Node final_node(final_vector);

    if (!ParityPosition(start_node)) {
        fout << "-1\n";
    } else {
        pair<string, int> result = AStar(start_node, final_node);
        fout << result.second << "\n" << result.first ;
    }

    return 0;
}