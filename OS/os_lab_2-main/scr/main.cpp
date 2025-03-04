#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>

// функция для сортировки массива методом четно-нечетной сортировки. Принимает ссылку на вектор и диапазон элементов для сортировки.
void oddevenSort(std::vector<int>& arr, int start, int end) {
    bool sorted = false; // проверка, отсортирован ли массив на текущей итерации.
    while (!sorted) {
        sorted = true;
        for (int i = start; i < end - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        for (int i = start + 1; i < end - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}


// главная функция программы. Принимает аргументы командной строки.
int main(int argc, char* argv[]) {
    if (argc != 2) { // проверка на количество аргументов командной строки.
        std::cerr << "Usage: " << argv[0] << " <numThreads>" << std::endl;
        return 1;
    }

    int numThreads = std::stoi(argv[1]); // преобразование аргумента командной строки в число потоков.

// вводим число элементов массива
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;

// вводим элементы массивы
    std::vector<int> arr(n);
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

// засекаем начальное время выполнения программы
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now(); 

// Программа создает numThreads потоков, вызывая функцию oddevenSort для разбиения массива на части для  сортировки и после чего ожидает завершения всех потоков.
    std::vector<std::thread> threads; 
    int chunkSize = n / numThreads;
    for (int i = 0; i < numThreads; i++) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;
        threads.push_back(std::thread(oddevenSort, std::ref(arr), start, end));
    }

// Дожидаемся завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    // Объединение отсортированных подмассивов.
    for (int step = 2; step < n; step *= 2) {
        for (int i = 0; i < n; i += step * 2) {
            int mid = std::min(i + step, n);
            int end = std::min(i + step * 2, n);
            std::inplace_merge(arr.begin() + i, arr.begin() + mid, arr.begin() + end);
        }
    }

    std::cout << "Sorted array: ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

// программа останавливает таймер, вычисляет продолжительность выполнения программы и выводит её в микросекундах.
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время работы программы: " << duration.count() << " микросекунд. " << "\n";

return 0;
}
