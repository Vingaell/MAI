#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

int getMaxWidth(const std::vector<std::pair<unsigned long long, unsigned long long>>& data) {
    unsigned long long maxNumber = 0;
    for (const auto& elem : data) {
        maxNumber = std::max({maxNumber, elem.first, elem.second}); 
    }
    return static_cast<int>(std::to_string(maxNumber).size());
}

void radixSort(std::vector<std::pair<unsigned long long, unsigned long long>>& data) {
    const int RADIX = 10;
    int WIDTH = getMaxWidth(data);

    std::vector<std::pair<unsigned long long, unsigned long long>> tmp(data.size());

    for (int i = 0; i < WIDTH; ++i) {
        std::vector<int> count(RADIX, 0);

        for (const auto& elem : data) {
            int digit = (elem.first / static_cast<unsigned long long>(std::pow(10, i))) % RADIX;
            count[digit]++;
        }

        for (int j = 1; j < RADIX; ++j) {
            count[j] += count[j - 1];
        }

        for (int j = data.size() - 1; j >= 0; --j) {
            int digit = (data[j].first / static_cast<unsigned long long>(std::pow(10, i))) % RADIX;
            tmp[count[digit] - 1] = data[j];
            count[digit]--;
        }

        data = tmp;
    }
}

int main() {
    std::ifstream file("input.txt");

    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<std::pair<unsigned long long, unsigned long long>> data;
    unsigned long long key, value;

    while (file >> key >> value) {
        data.push_back(std::make_pair(key, value));
    }

    file.close();

    radixSort(data);

    for (const auto& elem : data) {
        std::cout << elem.first << "\t" << elem.second << std::endl;
    }

    return 0;
}