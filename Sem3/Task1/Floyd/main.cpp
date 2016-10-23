//Фаттахов
//Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу
//кратчайших путей между его вершинами.
//Гарантируется, что в графе нет циклов отрицательного веса.
//Формат входного файла
//В первой строке вводится единственное число 𝑁 (1 6 𝑁 6 100) — количество вершин графа. В
//следующих 𝑁 строках по 𝑁 чисел задается матрица смежности графа (𝑗-ое число в 𝑖-ой строке —
//вес ребра из вершины 𝑖 в вершину 𝑗). Все числа по модулю не превышают 100. На главной диагонали
//матрицы — всегда нули.
//Формат выходного файла
//Выведите 𝑁 строк по 𝑁 чисел — матрицу расстояний между парами вершин, где 𝑗-ое число в
//𝑖-ой строке равно весу кратчайшего пути из вершины 𝑖 в 𝑗.

#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::cin;
using std::cout;

int main(){
    std::ifstream fin("floyd.in");
    std::ofstream fout("floyd.out");
    vector< vector<float> > matrix;
    int vert_num = 0;
    fin >> vert_num;
    // Ввод матрицы смежности.
    for (int i = 0; i < vert_num; ++i) {
        vector<float> tmp_vector;
        matrix.push_back(tmp_vector);
        for (int j = 0; j < vert_num; ++j) {
            float tmp_edge;
            fin >> tmp_edge;
            matrix[i].push_back(tmp_edge);
        }
    }

    // Флойд: на каждой итерации сравниваем расстояние, если улучшилось, изменяем.
    for (int i = 0; i < vert_num; ++i) {
        for (int j = 0; j < vert_num; ++j) {
            for (int k = 0; k < vert_num; ++k) {
                matrix[j][k] = std::min(matrix[j][k], matrix[j][i] + matrix[i][k]);
            }
        }
    }

    // Вывод получившейся матрицы.
    for (int i = 0; i < vert_num; ++i) {
        for (int j = 0; j < vert_num; ++j) {
            fout << matrix[i][j];
            if (j != vert_num - 1) {
                fout << " ";
            }
        }
        if (i != vert_num - 1) {
            fout << "\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}