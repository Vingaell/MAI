#include "NPC.hpp"
#include <memory>

std::shared_ptr<NPC> factory(std::istream&);

std::shared_ptr<NPC> factory(const std::string&, const std::string&, const int&, const int&);
