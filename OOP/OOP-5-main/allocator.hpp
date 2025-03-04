#pragma once
#include <memory>
#include <vector>

namespace mai {
template <class T, size_t SIZE = 1000>
class Allocator {
   public:
    std::vector<T> data;
    size_t free_slots;

    using value_type = T;
    using pointer = T*;
    using const_ointer = const T*;
    using size_type = size_t;

    Allocator() {
        data.resize(SIZE);
        free_slots = SIZE;
    }

    ~Allocator() = default;

    auto allocate(size_t n) -> pointer {
        if (n > free_slots) {
            throw std::bad_alloc();
        }

        free_slots -= n;

        return &data[free_slots];
    }

    auto deallocate(pointer p, size_t n) -> void {
        free_slots += n;
    }

    template <class U, class... Args>
    auto construct(U* p, Args&&... args) -> void {
        new (p) U(std::forward<Args>(args)...);
    }

    auto destroy(pointer p) -> void {
        p->~T();
    }

    template <class U>
    struct rebind {
        using other = Allocator<U>;
    };
};

template <class T, class U>
constexpr auto operator==(const Allocator<T>& lhs, const Allocator<U>& rhs) -> bool {
    return true;
}

template <class T, class U>
constexpr auto operator!=(const Allocator<T>& lhs, const Allocator<U>& rhs) -> bool {
    return false;
}

}  // namespace mai