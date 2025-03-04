#pragma once
#include "npc.hpp"

struct Ork : public NPC
{
    Ork(int x, int y);
    Ork(std::istream &is);

    void print() override;

    void save(std::ostream &os) override;
    
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Ork> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    friend std::ostream &operator<<(std::ostream &os, Ork &Ork);

    bool accept(std::shared_ptr<NPC> visitor) override;
};
