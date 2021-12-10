#include <iostream>
#include <position.hpp>

std::vector<int> range(const int start, const int end, const int step);
std::vector<std::tuple<int, int> > zip(const std::vector<int>* a, const std::vector<int>* b);

// Position definitions
// Algebraic constructor
Position::Position(const std::string str)
    : i(str[1] - 49), j(str[0] - 65) {};

// Equalty operator (maybe use hash)
bool Position::operator==(const Position &other) const
{ return this->i == other.i && this->j == other.j; };

// Not equal operator
bool Position::operator!=(const Position &other) const
{ return this->i != other.i || this->j != other.j; };

// Less than operator (for std::map)
bool Position::operator<(const Position& rhs) const
{ return this->i < rhs.i && this->j < rhs.j; };

// Addition operator for Position and Vec
Position Position::operator+(const Vec &vec) const
{ return Position(this->i + vec.i, this->j + vec.j); };

// Subtraction operator for Position and Vec
Position Position::operator-(const Vec &vec) const
{ return Position(this->i - vec.i, this->j - vec.j); };

// Python hash function
int Position::__hash__() const
{ return 0 | (this->i<<3) | (this->j); };

// Python repr function
std::string Position::__repr__() const
{
    // I am sure this is very ugly lol
    std::string s = "";
    s = s + (char)(this->j + 65);
    s = s + (char)(this->i + 49);
    return s;
}

bool Position::is_valid()
{ return i > -1 && i < 8 && j > -1 && j < 8; };

MoveSet Position::path_to(Position& other)
{
    int di = other.i - this->i;
    int dj = other.j - this->j;
    int ai = abs(di);
    int aj = abs(dj);
    std::vector<Position> moves;
    
    // Copy sign macro
    auto sign = [](const int& d){ return copysign(1, d); };

    // Get the ranges of each axis
    auto ri = range(0, di, sign(di));
    auto rj = range(0, dj, sign(dj));
    
    // Pass the ranges ri and rj into zip
    // Use that to construct position.

    if (ri.size() == rj.size())
    {
        // Set up pointers and zip the two lists together
        std::vector<int>* ri_ptr = &ri;
        std::vector<int>* rj_ptr = &rj;
        auto ziplist = zip(ri_ptr, rj_ptr);
        
        // Iterate through all the pairs in the list and construct a position
        // from them
        for (auto tpl : ziplist)
            { moves.push_back(Position(std::get<0>(tpl), std::get<1>(tpl))); }
    }
    else if (di == 0)
    {
        for (int i : rj)
            { moves.push_back(Position(this->i, this->j + i)); }
    }
    else if (dj == 0)
    {
        for (int i : ri)
            { moves.push_back(Position(this->i + i, this->j)); }
    }
    else
    {
        moves.push_back(Position(this->i, this->j));
    }
    return moves;
}

Vec Vec::operator*(int &scalar) const
{ return Vec(this->i * scalar, this->j * scalar); }

// Vector definitions
Vec operator*(Vec &vec, int &scalar)
{ return Vec(vec.i * scalar, vec.j * scalar); };

Vec operator*(int &scalar, Vec &vec)
{ return Vec(vec.i * scalar, vec.j * scalar); };



// HELPERS
// Range function!
std::vector<int> range(const int start, const int end, const int step)
{
    auto out = std::vector<int>{};
    for (int i = start; i != end; i += step)
    { out.push_back(i); };
    return out;
}

// Zip function!
std::vector<std::tuple<int, int> > zip(const std::vector<int>* a, const std::vector<int>* b)
{
    std::vector<std::tuple<int, int> > out;
    auto a_it = std::begin(*a);
    auto b_it = std::begin(*b);
    
    for (; a_it != std::end(*a) && b_it != std::end(*b); ++a_it, ++b_it)
    {
        out.push_back(std::tuple<int, int>{*a_it, *b_it});
    }
    return out;
}
