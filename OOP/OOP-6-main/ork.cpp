#include "squirrel.hpp"
#include "bear.hpp"
#include "ork.hpp"

Ork::Ork(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    status = true;
}

void Ork::print(std::ostream& out) 
{
    out << *this;
}

 void Ork::accept(NPC* attacker, const int& distance) {}

std::ostream& operator<<(std::ostream& out, const Ork& other) 
{
    return out << "Ork " << other.name << " {" << other.x << ", " << other.y << '}';
}
