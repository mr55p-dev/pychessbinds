#include <iostream>
#include <position.hpp>

// Position definitions
Position::Position(int init_i, int init_j) : i(init_i), j(init_j) {};

Position& Position::operator++() {
    ++i;
    ++j;
    return *this;
};

bool Position::operator==(const Position &other) const
{ return this->i == other.i && this->j == other.j; };

bool Position::operator<(const Position& rhs) const
{ return this->i < rhs.i && this->j < rhs.j; };

Position operator+(const Position &pos, Vec &vec)
{ return Position(pos.i + vec.i, pos.j + vec.j); }

Position operator+(Vec &vec, const Position &pos)
{ return Position(pos.i + vec.i, pos.j + vec.j); }

bool Position::is_valid()
{ return i > -1 && i < 8 && j > -1 && j < 8; };


Vec Vec::operator*(int &scalar) const
{ return Vec(this->i * scalar, this->j * scalar); }

//// Vector definitions
//Vec operator*(Vec &vec, int &scalar) const
//{ return Vec(vec.i * scalar, vec.j * scalar); };
//
//Vec operator*(int &scalar, Vec &vec) const
//{ return Vec(vec.i * scalar, vec.j * scalar); };
