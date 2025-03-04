#include "ork.hpp"
#include "squirrel.hpp"
#include "bear.hpp"

Ork::Ork(int x, int y) : NPC(OrkType, x, y) {}
Ork::Ork(std::istream &is) : NPC(OrkType, is) {}

void Ork::print()
{
    std::cout << *this;
}

bool Ork::accept(std::shared_ptr<NPC> visitor)
{
    return visitor->fight(std::shared_ptr<Ork>(this,[](Ork*){}));
}

void Ork::save(std::ostream &os)
{
    os << OrkType << std::endl;
    NPC::save(os);
}

bool Ork::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, true);
    return true;
}

bool Ork::fight(std::shared_ptr<Ork> other)
{
    fight_notify(other, false);
    return false;
}

bool Ork::fight(std::shared_ptr<Squirrel> other)
{
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, Ork &Ork)
{
    os << "Ork: " << *static_cast<NPC *>(&Ork) << std::endl;
    return os;
}
