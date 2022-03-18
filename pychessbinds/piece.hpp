/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


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
    bool is_active;
public:
    Piece(Position start_position,
          const char init_kind,
          const bool init_colour,
          int distance,
          const ProjectionSet init_projections
    );
    bool operator<(const Piece& rhs) const;
    bool operator==(const Piece& rhs) const;
    bool operator!=(const Piece& rhs) const;
    int hash() const;
};

namespace Piecedef
{
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


    // Define a constant for the default value of the BasePiece constructing function
    const ProjectionSet all_projections(Piecedef::all_projection_list, Piecedef::all_projection_list + 8);

    Piece BasePiece(
                    const bool colour,
                    const Position starting_position,
                    const char kind,
                    int max_distance = 7,
                    const ProjectionSet projections = all_projections,
                    bool is_active = false);
    Piece King(bool colour, Position starting_position);
    Piece Queen(bool colour, Position starting_position);
    Piece Rook(bool colour, Position starting_position);
    Piece Knight(bool colour, Position starting_position);
    Piece Bishop(bool colour, Position starting_position);
    Piece Pawn(bool colour, Position starting_position);

};
