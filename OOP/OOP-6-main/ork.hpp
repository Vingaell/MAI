#pragma once
#include "NPC.hpp"

class Ork: public NPC 
{
    public:
        Ork(const int&, const int&, const std::string&);

        void print(std::ostream&) override;

        void accept(NPC*, const int&) override;

        friend std::ostream& operator<<(std::ostream&, const Ork&);
};
