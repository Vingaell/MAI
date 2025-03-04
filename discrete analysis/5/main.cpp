#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Vertex {
    int l, r;  // Диапазон символов в строке
    vector<int> children;  // Дети вершины
    vector<int> positions;  // Позиции суффиксов

    Vertex() : l(-1), r(-1), children(27, -1) {}
};

class TSuffixTree {
public:
    TSuffixTree(const string& inputText) : text(inputText) {
        text += '$';  // Добавляем специальный символ, который гарантированно не встречается в тексте
        root = 0;  // Корень дерева
        go.push_back(Vertex());  // Добавляем корень
        buildSuffixTree();  // Строим суффиксное дерево
    }

    // Функция поиска подстроки
    vector<int> search(const string& pattern) {
        int cur = root;
        int l = 0;
        while (l < pattern.size()) {
            int ch = toIndex(pattern[l]);
            int next = go[cur].children[ch];
            if (next == -1) {
                return {};  // Подстрока не найдена
            }
            int start = go[next].l;
            int end = go[next].r;
            for (int i = start; i < end && l < pattern.size(); ++i, ++l) {
                if (text[i] != pattern[l]) {
                    return {};  // Если символы не совпадают, выходим
                }
            }
            cur = next;
        }
        return collectPositions(cur);  // Собирать все позиции
    }

private:
    string text;  // Исходный текст
    vector<Vertex> go;  // Массив вершин дерева
    int root;  // Индекс корня
    int count = 1;  // Счётчик для новых вершин

    // Строим суффиксное дерево
    void buildSuffixTree() {
        for (int i = 0; i < text.size(); ++i) {
            insert(i);  // Вставляем суффиксы
        }
    }

    // Вставка суффикса в дерево
    void insert(int l) {
        int cur = root;
        int pos = l;

        while (pos < text.size()) {
            int ch = toIndex(text[pos]);
            if (go[cur].children[ch] == -1) {
                createVertex(cur, pos, text.size());  // Создаем вершину, если её нет
                go[count - 1].positions.push_back(l);  // Добавляем текущую позицию
                return;
            }
            int next = go[cur].children[ch];
            int start = go[next].l;
            int end = go[next].r;
            bool split = false;

            for (int i = start; i < end && pos < text.size(); ++i, ++pos) {
                if (text[i] != text[pos]) {
                    split = true;
                    createVertex(cur, go[next].l, i);  // Разделяем вершины
                    go[count - 1].children[toIndex(text[i])] = next;
                    go[next].l = i;

                    // Переносим все позиции
                    for (int position : go[next].positions) {
                        go[count - 1].positions.push_back(position);
                    }
                    cur = count - 1;
                    break;
                }
            }

            if (!split) {
                cur = next;  // Если разбиение не требуется, просто переходим
            }
        }

        if (find(go[cur].positions.begin(), go[cur].positions.end(), l) == go[cur].positions.end()) {
            go[cur].positions.push_back(l);  // Добавляем позицию суффикса
        }
    }

    // Создание вершины
    void createVertex(int cur, int l, int r) {
        go.push_back(Vertex());
        go[count].l = l;
        go[count].r = r;
        go[cur].children[toIndex(text[l])] = count++;  // Создаем вершину для суффикса
    }

    // Сбор позиций для найденного суффикса
    vector<int> collectPositions(int cur) {
        vector<int> positions;
        collectPositionsDFS(cur, positions);  // Рекурсивно собираем все позиции
        return positions;
    }

    // Рекурсивный сбор всех позиций
    void collectPositionsDFS(int cur, vector<int>& positions) {
        for (int pos : go[cur].positions) {
            if (find(positions.begin(), positions.end(), pos) == positions.end()) {
                positions.push_back(pos);
            }
        }
        for (int i = 0; i < 27; ++i) {
            if (go[cur].children[i] != -1) {
                collectPositionsDFS(go[cur].children[i], positions);  // Рекурсивно обрабатываем детей
            }
        }
    }

    // Преобразуем символ в индекс
    int toIndex(char ch) {
        return (ch == '$') ? 26 : (ch - 'a');  // '$' — это 26-й символ
    }
};

int main() {
    string text;
    cin >> text;
    TSuffixTree tree(text);

    string pattern;
    int count = 1;
    while (cin >> pattern) {
        vector<int> res = tree.search(pattern);

        if (!res.empty()) {
            cout << count << ": ";
            sort(res.begin(), res.end());
            for (int i = 0; i < res.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << res[i] + 1;  // Индексация с 1
            }
            cout << endl;
        }
        ++count;
    }
    return 0;
}