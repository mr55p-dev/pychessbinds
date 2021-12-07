#include <iostream>
#include <vector>
#include "log.hpp"

void Log(const char* message) 
{
    std::cout << message << std::endl;
}

void Log(const Piece* piece)
{
    std::cout << "<Piece '" << piece->kind << "' colour " << piece->colour << " at " << piece->position.i << ", " << piece->position.j << " with " << piece->projections.size() << " projections" << ">" << std::endl;
}

void Log(const Vec* vec)
{
    std::cout << "<Vector i:" << vec->i << " j:" << vec->j << ">" << std::endl;
};

void Log(const Position* pos)
{
    std::cout << "<Position " << pos->i << ", " << pos->j << ">" << std::endl;
}

void Log(const ProjectionSet* list)
{
    Log("Projections:");
    for (auto i: *list) { Log(&i); }
}

void Log(const MoveSet* moveset)
{
    std::cout << "[[";
    for (auto i: *moveset) { std::cout << "\t"; Log(&i); };
    std::cout << "]]" << std::endl;
};
