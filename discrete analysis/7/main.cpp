#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Segment {
    int start, end, index;
    Segment(int s, int e, int i) : start(s), end(e), index(i) {}
};

bool compareByStart(const Segment &a, const Segment &b) {
    return a.start < b.start;
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    if (!input) {
        std::cerr << "Не удалось открыть файл input.txt!" << std::endl;
        return 1;
    }

    int N, M;
    input >> N;
    std::vector<Segment> segments;

    for (int i = 0; i < N; ++i) {
        int L, R;
        input >> L >> R;
        segments.push_back(Segment(L, R, i));
    }
    input >> M;

    // Сортируем отрезки по левой границе
    std::sort(segments.begin(), segments.end(), compareByStart);

    std::vector<Segment> result;
    int current_right = 0, next_right = 0;
    size_t i = 0;

    while (current_right < M) {
        bool found = false;
        Segment best_segment(0, 0, -1);

        // Найти лучший отрезок, который можно использовать для расширения покрытия
        while (i < segments.size() && segments[i].start <= current_right) {
            if (segments[i].end > next_right) {
                next_right = segments[i].end;
                best_segment = segments[i];
                found = true;
            }
            ++i;
        }

        if (!found) {
            output << "0" << std::endl;
            return 0;
        }

        result.push_back(best_segment);
        current_right = next_right;
    }

    // Сортируем выбранные отрезки по их индексу в исходном массиве для вывода в правильном порядке
    std::sort(result.begin(), result.end(), [](const Segment &a, const Segment &b) {
        return a.index < b.index;
    });

    // Вывод результата в файл
    output << result.size() << std::endl;
    for (const auto &seg : result) {
        output << seg.start << " " << seg.end << std::endl;
    }

    return 0;
}