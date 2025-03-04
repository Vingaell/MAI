#pragma once
#include <string>
 
class Octal
{
    private:
        unsigned char *s_array;
        std::size_t s_size;
        void resize_arr(const size_t);
 
    public:
        Octal();
        Octal(const std::size_t &, unsigned char);
        Octal(const std::initializer_list<unsigned char> &);
        Octal(const std::string &);
        Octal(const Octal&);
        Octal(Octal&& other) noexcept;
        ~Octal() noexcept;
 
        Octal operator + (const Octal&);
        Octal operator - (const Octal&);
        Octal operator = (const Octal&);
        bool operator < (const Octal&);
        bool operator > (const Octal&);
        bool operator == (const Octal&);
 
        std::string to_string() const;
};