#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace std;

// Функция для вычисления максимальной площади в "гистограмме"
int maxHistogramArea(const vector<int>& heights) {
    stack<int> s;
    int maxArea = 0, n = heights.size();

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && heights[s.top()] > heights[i]) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        s.push(i);
    }

    // Обрабатываем оставшиеся элементы в стеке
    while (!s.empty()) {
        int height = heights[s.top()];
        s.pop();
        int width = s.empty() ? n : n - s.top() - 1;
        maxArea = max(maxArea, height * width);
    }

    return maxArea;
}

// Основная функция для поиска максимальной площади прямоугольника из нулей
int maxRectangle(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;

    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> heights(m, 0); // Гистограмма для текущей строки
    int maxArea = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Если текущий элемент 0, увеличиваем высоту гистограммы
            heights[j] = (matrix[i][j] == 0) ? heights[j] + 1 : 0;
        }
        // Находим максимальную площадь для текущей гистограммы
        maxArea = max(maxArea, maxHistogramArea(heights));
    }

    return maxArea;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Ошибка при открытии файлов!" << endl;
        return 1;
    }

    int n, m;
    input >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char ch;
            input >> ch;
            matrix[i][j] = ch - '0'; // Преобразуем символ в число
        }
    }

    int result = maxRectangle(matrix);

    output << result << endl;

    input.close();
    output.close();

    return 0;
}