#include "squirrel.hpp"
#include "bear.hpp"
#include "ork.hpp"

Bear::Bear(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    status = true;
}

void Bear::print(std::ostream& out) 
{
    out << *this;
}

void Bear::accept(NPC* attacker, const int& distance) 
{
    if (status && dynamic_cast<Ork*>(attacker)) 
    {
        bool win = is_close(*attacker, distance);
        if (win) status = false;
        
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Bear& other) 
{
    return out << "Bear " << other.name << " {" << other.x << ", " << other.y << '}';
}
