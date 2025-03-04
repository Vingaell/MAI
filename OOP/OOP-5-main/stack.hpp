#pragma once
#include <memory>

namespace mai {
template <class T, size_t MAX_SIZE = 100, class Alloc = std::allocator<T>>
class Stack {
   private:
    T** _data;
    size_t _size;

    using Alloc_traits = std::allocator_traits<Alloc>;
    Alloc _alloc;

   public:
    class Iterator {
       private:
        friend Stack;
        T** _p;

       public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator()
            : _p(nullptr) {}

        Iterator(T** p)
            : _p(p) {}

        ~Iterator() noexcept {
            _p = nullptr;
        }

        inline auto operator*() const -> reference {
            return **_p;
        }

        inline auto operator++() -> Iterator& {
            ++_p;
            return *this;
        }

        inline auto operator++(int) -> Iterator {
            Iterator tmp = *this;
            ++_p;
            return tmp;
        }

        inline auto operator==(const Iterator& other) const -> bool {
            return _p == other._p;
        }

        inline auto operator!=(const Iterator& other) const -> bool {
            return _p != other._p;
        }
    };

    class ConstIterator {
       private:
        friend Stack;
        T** _p;

       public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        ConstIterator()
            : _p(nullptr) {}

        ConstIterator(T** p)
            : _p(p) {}

        ~ConstIterator() noexcept {
            _p = nullptr;
        }

        inline auto operator*() const -> value_type {
            value_type res = **_p;
            return res;
        }

        inline auto operator++() -> ConstIterator& {
            ++_p;
            return *this;
        }

        inline auto operator++(int) -> ConstIterator {
            ConstIterator tmp = *this;
            ++_p;
            return tmp;
        }

        inline auto operator==(const ConstIterator& other) const -> bool {
            return _p == other._p;
        }

        inline auto operator!=(const ConstIterator& other) const -> bool {
            return _p != other._p;
        }
    };

    auto begin() noexcept -> Iterator {
        return Iterator(_data);
    }

    auto end() noexcept -> Iterator {
        return Iterator(_data + _size);
    }

    auto cbegin() const noexcept -> ConstIterator {
        return ConstIterator(_data);
    }

    auto cend() const noexcept -> ConstIterator {
        return ConstIterator(_data + _size);
    }

    Stack()
        : _size(0), _alloc() { _data = new T*[MAX_SIZE]; }

    Stack(const Stack<T, MAX_SIZE, Alloc>& other) {
        _size = other._size;
        for (size_t i = 0; i != _size; ++i) {
            _data[i] = Alloc_traits::allocate(_alloc, 1);
            *_data[i] = *other._data[i];
        }
    }

    ~Stack() noexcept {
        for (size_t i = 0; i != _size; ++i) {
            Alloc_traits::destroy(_alloc, _data[i]);
            Alloc_traits::deallocate(_alloc, _data[i], 1);
        }

        delete[] _data;
        _size = 0;
    }

    inline auto size() const -> size_t {
        return _size;
    }

    inline auto empty() const -> bool {
        return _size == 0;
    }

    inline auto push(const T& element) -> void {
        _data[_size] = Alloc_traits::allocate(_alloc, 1);
        *_data[_size] = element;
        _size++;
    }

    inline auto pop() -> T {
        _size--;
        T value = *_data[_size];
        Alloc_traits::destroy(_alloc, _data[_size]);
        Alloc_traits::deallocate(_alloc, _data[_size], 1);
        return value;
    }

    inline auto operator=(const Stack<T, MAX_SIZE, Alloc>& other) -> Stack& {
        for (size_t i = 0; i != _size; ++i) {
            Alloc_traits::destroy(_alloc, _data[i]);
            Alloc_traits::deallocate(_alloc, _data[i], 1);
        }

        _size = other._size;

        for (size_t i = 0; i != _size; ++i) {
            _data[i] = Alloc_traits::allocate(_alloc, 1);
            *_data[i] = *other._data[i];
        }

        return *this;
    }

    inline auto operator[](size_t index) const -> T {
        T value = *_data[index];
        return value;
    }
};

template <class T, size_t MAX_SIZE = 100, class Alloc>
inline auto operator<<(std::ostream& os, const Stack<T, MAX_SIZE, Alloc>& s) -> std::ostream& {
    os << "Stack elements: ";

    for (size_t i = 0; i != s.size(); ++i) {
        os << s[i] << " ";
    }

    return os;
}
}  // namespace mai