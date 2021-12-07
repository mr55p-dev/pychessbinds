#include <iostream>
#include <position.hpp>

// Position definitions
Position::Position(int init_i, int init_j) : i(init_i), j(init_j) {};
Position& Position::operator++() {
    ++i;
    ++j;
    return *this;
};

Position operator+(const Position &pos, Vec &vec)
{ return Position(pos.i + vec.i, pos.j + vec.j); }

Position operator+(Vec &vec, const Position &pos)
{ return Position(pos.i + vec.i, pos.j + vec.j); }

bool Position::is_valid()
{ return i > -1 && i < 8 && j > -1 && j < 8; };


// Vector definitions
Vec operator*(Vec &vec, int &scalar)
{ return Vec(vec.i * scalar, vec.j * scalar); };

Vec operator*(int &scalar, Vec &vec)
{ return Vec(vec.i * scalar, vec.j * scalar); };
