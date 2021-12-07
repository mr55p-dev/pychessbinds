#pragma once

// Vector struct
class Vec
{
public:
    const int i;
    const int j;
    
public:
    Vec(const int start_i, const int start_j) : i(start_i), j(start_j) {};
    friend Vec operator*(Vec &vec, int &scalar);
    friend Vec operator*(int &scalar, Vec &vec);
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
    friend Position operator+(const Position &pos, Vec &vec);
    friend Position operator+(Vec &vec, const Position &pos);

};

// Type definition
typedef std::vector<Position> MoveSet;
