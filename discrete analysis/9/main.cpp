#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 110000;

vector<int> adj[MAXN]; // Списки смежности
vector<int> match;     // Сопоставленные вершины
vector<bool> used;     // Вектор для отслеживания посещений вершин

// Алгоритм Куна для поиска увеличивающей цепочки
bool kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;

    for (int to : adj[v]) {
        if (match[to] == -1 || kuhn(match[to])) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    // Чтение графа
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Сортировка списков смежности для обеспечения однозначности
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }

    // Инициализация массивов
    match.assign(n + 1, -1);

    // Основной алгоритм Куна
    for (int v = 1; v <= n; v++) {
        used.assign(n + 1, false);
        kuhn(v);
    }


    // Формирование результата
    vector<pair<int, int>> matching;
    for (int v = 1; v <= n; v++) {
        if (match[v] != -1 && v > match[v]) {
            matching.emplace_back(match[v], v);
        }
    }

    sort(matching.begin(), matching.end()); // Сортировка рёбер

    // Вывод результата
    fout << matching.size() << "\n";
    for (auto &edge : matching) {
        fout << edge.first << " " << edge.second << "\n";
    }

    return 0;
}