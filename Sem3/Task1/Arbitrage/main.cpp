// Необходимо написать торгового советника для поиска арбитража.
// Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:
// GBP/USD: 0.67
// RUB/GBP: 78.66
// USD/RUB: 0.02
// Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using std::cin;
using std::cout;
using std::vector;

bool Ford(const vector< vector<double> > &Edges, int vertNum) {
    vector<double> distance(vertNum, 0);
    distance[0] = 1;
    // Итерируемся |Edges| - 1  раз
    for (int i = 0; i < Edges.size() - 1; ++i) {
        bool relax = false;
        // Релаксируем все ребра внутри итерации.
        for (int j = 0; j < Edges.size(); ++j) {
            for (int k = 0; k < Edges.size(); ++k) {
                if (distance[k] < distance[j] * Edges[j][k] && Edges[j][k] > 0 ) {
                    distance[k] = distance[j] * Edges[j][k];
                    relax = true;
                }
            }
        }
        // Если нет релаксаций, то конец работы.
        if (!relax) {
            break;
        }
    }
    // Если есть неотрелаксированное ребро, то есть цикл.
    for (int j = 0; j < Edges.size(); ++j) {
        for (int k = 0; k < Edges.size(); ++k) {
            if (distance[k] < distance[j] * Edges[j][k] && Edges[j][k] > 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Двумерный массив смежности.
    vector<vector<double> > Edges;
    int vertNum = 0;
    cin >> vertNum;

    // Ввод графа.
    for (int i = 0; i < vertNum; ++i) {
        vector<double> tmpVect;
        Edges.push_back(tmpVect);
        for (int j = 0; j < vertNum; ++j) {
            // Заполняем диагональные элементы нулями(валюту на себя менять не выгодно).
            if (i == j) {
                Edges[i].push_back(0);
            } else {
                double tmpEdge;
                cin >> tmpEdge;
                Edges[i].push_back(tmpEdge);

            }
        }
    }
    // Проверка, есть ли положительный цикл.
    if (Ford(Edges, vertNum)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}