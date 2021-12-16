/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


#include <iostream>
#include <vector>
#include "log.hpp"

void Log(const char* message) 
{
    std::cout << message << std::endl;
}

void Log(const Piece* piece)
{
    std::cout << "<Piece '" << piece->kind << "' colour " << piece->colour << " at " << piece->position.__repr__() << " with " << piece->projections.size() << " projections" << ">" << std::endl;
}

void Log(const Vec* vec)
{
    std::cout << "<Vector i:" << vec->i << " j:" << vec->j << ">" << std::endl;
};

void Log(const Position* pos)
{
    std::cout << pos->__repr__() << std::endl;
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
