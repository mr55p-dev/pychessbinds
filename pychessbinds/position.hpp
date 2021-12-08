#pragma once

// Vector struct
class Vec
{
public:
    const int i;
    const int j;
    
public:
    Vec(const int start_i, const int start_j) : i(start_i), j(start_j) {};
    Vec operator*(int &scalar) const;
};

// Position class
class Position
{
public:
    int i;
    int j;

public:
    bool is_valid();
    
public:
    Position(int init_i, int init_j);
    Position& operator++();
    bool operator==(const Position &other) const;
    bool operator<(const Position &rhs) const;
    friend Position operator+(const Position &pos, Vec &vec);
    friend Position operator+(Vec &vec, const Position &pos);

};

// Type definition
typedef std::vector<Position> MoveSet;
