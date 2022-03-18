#include <iostream>
#include "position.hpp"
#include "piece.hpp"


Piece::Piece(
             Position start_position,
             const char init_kind,
             const bool init_colour,
             const int init_distance,
             const ProjectionSet init_projections) :

    position(start_position.i, start_position.j),
    kind(init_kind),
    colour(init_colour),
    projections(init_projections),
    distance(init_distance),
    is_active(true) {};

bool Piece::operator< (const Piece& rhs) const
{ return true; };

bool Piece::operator== (const Piece& rhs) const
{
    return this->hash() == rhs.hash();
}

bool Piece::operator!= (const Piece& rhs) const
{
    return this->hash() != rhs.hash();
};

int Piece::hash() const
{
    return 0 | this->position.i<<12 | this->position.j<<9 | this->kind<<2 | this->is_active<<1 | this->colour;
}

Piece BasePiece(
                const bool colour,
                const Position starting_position,
                const char kind,
                int max_distance,
                const ProjectionSet projections,
                bool is_active)
{
    Piece piece(starting_position, kind, colour, max_distance, projections);
    return piece;}


Piece Piecedef::King(bool colour, Position starting_position)
{
    const ProjectionSet proj(Piecedef::all_projection_list, Piecedef::all_projection_list + 8);
    Piece king(starting_position, 'K', colour, 1, proj);
    return king;
}

Piece Piecedef::Queen(bool colour, Position starting_position)
{
    const ProjectionSet proj(Piecedef::all_projection_list, Piecedef::all_projection_list + 8);
    Piece queen(starting_position, 'Q', colour, 7, proj);
    return queen;
}

Piece Piecedef::Rook(bool colour, Position starting_position)
{
    const ProjectionSet proj(Piecedef::rook_projection_list, Piecedef::rook_projection_list + 4);
    Piece rook(starting_position, 'R', colour, 7, proj);
    return rook;
}

Piece Piecedef::Bishop(bool colour, Position starting_position)
{
    const ProjectionSet proj(Piecedef::bishop_projection_list, Piecedef::bishop_projection_list + 4);
    Piece bishop(starting_position, 'B', colour, 7, proj);
    return bishop;
}

Piece Piecedef::Knight(bool colour, Position starting_position)
{
    const ProjectionSet proj(Piecedef::knight_projection_list, Piecedef::knight_projection_list + 8);
    Piece knight(starting_position, 'N', colour, 1, proj);
    return knight;
}

Piece Piecedef::Pawn(bool colour, Position starting_position)
{
    if (colour)
    {
        ProjectionSet proj(Piecedef::pawn_projection_list_white, Piecedef::pawn_projection_list_white + 3);
        Piece pawn(starting_position, 'P', colour, 2, proj);
        return pawn;
    } else
    {
        ProjectionSet proj(Piecedef::pawn_projection_list_black, Piecedef::pawn_projection_list_black + 3);
        Piece pawn(starting_position, 'P', colour, 2, proj);
        return pawn;
    };
}
