/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <math.h>


// Vector struct
class Vec
{
public:
    const int i;
    const int j;
    
public:
    Vec(const int init_i, const int init_j) : i(init_i), j(init_j) {};
    Vec operator*(int &scalar) const;
    bool operator==(const Vec &rhs) const;
    bool operator!=(const Vec &rhs) const;
    Vec operator+(const Vec &rhs) const;
    Vec operator-(const Vec &rhs) const;
};

// Position class
class Position
{
public:
    int i;
    int j;

public:
    bool is_valid();
    std::vector<Position> path_to(const Position& other) const;
    
public:
    // Define a construct for Position(i, j)
    Position(const int init_i, const int init_j) : i(init_i), j(init_j) {};
    // Define a constructor for Position("E3")
    Position(const std::string);
    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
    bool operator<(const Position &rhs) const;
    
    Position operator+(const Vec &vec) const;
    Position operator-(const Vec &vec) const;
    
    
    int __hash__() const;
    std::string __repr__() const;
    std::string algebraic() const;
};

// Type definition
typedef std::vector<Position> MoveSet;
