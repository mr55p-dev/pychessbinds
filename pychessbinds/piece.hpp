#pragma once
#include <iostream>
#include <vector>
#include "position.hpp"

typedef std::vector<Vec> ProjectionSet;

class Piece
{
public:
    const bool colour;
    const char kind;
    const int distance;
    const Position position;
    const ProjectionSet projections;
public:
    Piece(Position start_position, const char init_kind, const bool init_colour, int distance, const ProjectionSet init_projections );
    bool operator<(const Piece& rhs) const;
};

namespace Piecedef
{
    Piece King(bool colour, Position starting_position);
    Piece Queen(bool colour, Position starting_position);
    Piece Rook(bool colour, Position starting_position);
    Piece Knight(bool colour, Position starting_position);
    Piece Bishop(bool colour, Position starting_position);
    Piece Pawn(bool colour, Position starting_position);
    
    const Vec all_projection_list[8] = {
        Vec(1, 1),
        Vec(1, 0),
        Vec(1, -1),
        Vec(0, 1),
        Vec(0, -1),
        Vec(-1, 1),
        Vec(-1, 0),
        Vec(-1, -1)
    };
    
    const Vec rook_projection_list[4] = {
        Vec(1, 0),
        Vec(-1, 0),
        Vec(0, 1),
        Vec(0, -1)
    };

    const Vec bishop_projection_list[4] = {
        Vec(1, 1),
        Vec(-1, -1),
        Vec(-1, 1),
        Vec(1, -1)
    };

    const Vec knight_projection_list[8] = {
        Vec(1, 2),
        Vec(1, -2),
        Vec(2, 1),
        Vec(2, -1),
        Vec(-1, 2),
        Vec(-1, -2),
        Vec(-2, 1),
        Vec(-2, -1)
    };

    const Vec pawn_projection_list_white[3] = {
        Vec(1, 0),
        Vec(1, -1),
        Vec(1, 1)
    };

    const Vec pawn_projection_list_black[3] = {
        Vec(-1, 0),
        Vec(-1, -1),
        Vec(-1, 1)
    };

};
