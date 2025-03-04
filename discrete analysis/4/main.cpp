#include <iostream>
#include <string>
#include <vector>

void zFunction(const std::string& s, std::vector<int>& z) {
    int n = s.length();
    z.resize(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

void searchPattern(const std::string& text, const std::string& pattern) {
    std::string concat = pattern + "$" + text;
    std::vector<int> z;
    zFunction(concat, z);
    int patternLength = pattern.length();
    for (int i = patternLength + 1; i < concat.length(); ++i) {
        if (z[i] == patternLength)
            std::cout << i - patternLength - 1 << std::endl;
    }
}

int main() {
    std::string text, pattern;
    std::cin >> text >> pattern;

    searchPattern(text, pattern);

    return 0;
}