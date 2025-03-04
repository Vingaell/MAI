#include "observer.hpp"
#include "NPC.hpp"
#include <memory>

void ConsoleObserver::update(NPC* defender, NPC* attacker, bool win) 
{
    if (!win) return;

    std::cout << "DIE: ";
    defender->print(std::cout);
    std::cout << " was killed by ";
    attacker->print(std::cout);
    std::cout << std::endl;
}

FileObserver::FileObserver(std::ofstream& _str) 
{
    _stream = std::make_unique<std::ofstream>(std::move(_str));
}

void FileObserver::update(NPC* defender, NPC* attacker, bool win) 
{
    if (!win) return;
    *_stream << "DIE: ";
    defender->print(*_stream);
    *_stream << " was killed by ";
    attacker->print(*_stream);
    *_stream << std::endl;
}
