#include <iostream>
#include <map>
#include "allocator.hpp"
#include "stack.hpp"

auto main() -> int {

    
     std::map<int, int, std::less<int>, mai::Allocator<std::pair<const int, int>>> m;
     m[0] = 1;
     for (size_t i = 1; i != 10; ++i) {
         m[i] = m[i - 1] * i;
     }

     std::cout << "Here are the elements of map: " << std::endl;
     for (auto [k, v] : m) {
         std::cout << k << " " << v << std::endl;
     }

    // Allocator with standard containers
    std::vector<int, mai::Allocator<int>> v(10);
    v[0] = 1;
    for (size_t i = 1; i != 10; ++i) {
        v[i] = v[i - 1] * i;
    }

    std::cout << "Here are the elements of a vector: " << std::endl;
    for (size_t i = 0; i != 10; ++i) {
        std::cout << i << " " << v[i] << std::endl;
    }
    std::cout << std::endl;

    // Custom STL container
    mai::Stack<int, 100, mai::Allocator<int>> s;
    for (size_t i = 0; i != 10; ++i)
        s.push(rand() % 100);

    std::cout << s << std::endl;

    for (size_t i = 0; i != 3; ++i)
        s.pop();

    std::cout << s << std::endl;

    for (size_t i = 0; i != 3; ++i)
        s.push(rand() % 100);

    std::cout << s << std::endl;

    return 0;
}
