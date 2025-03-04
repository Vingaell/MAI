#pragma once
#include <list>
#include "observer.hpp"

class Ork;
class Squirrel;
class Bear;

class NPC 
{
    protected:
        std::list<Observer*> observers;
        size_t x;
        size_t y;
        std::string name;
        bool status;

    public:
        NPC() = default;
        ~NPC() = default;

        virtual void print(std::ostream&) = 0;

        virtual void accept(NPC*, const int&) = 0;

        virtual void attach(Observer*);
        virtual void detach(Observer*);
        virtual void notify(NPC*, bool);

        virtual bool is_close(const NPC&, const int&) const noexcept;
        virtual bool is_alive() const noexcept;

        friend std::ostream& operator<<(std::ostream&, const NPC&);
};
