//
//  main.cpp
//  PyChessBinds
//
//  Created by Ellis Lunnon on 04/12/2021.
//

#include "test.hpp" 
#include "log.hpp"
#include "position.hpp"
#include "piece.hpp"

#define LOG(x) std::cout << x << std::endl;
#define _BREAKIF(cond) if (cond) {break;};

#include <map>
#include <array>
#include <vector>

// Can be moved into header
typedef std::map<MoveType, MoveSet > ResultSet;
typedef std::map<Position, int> PieceMap;
typedef std::map<Piece, MoveSet> MovesMap;

// psuedolegal moves
// psuedolegal move (by piece)
// projections
// step
// check allowed move
// create vector of new positions


namespace std
{
    // Override of std::less to allow it to work with Piece without having to define
    // > or < operators for it.
    template<> struct less<Piece>
    {
       bool operator() (const Piece& lhs, const Piece& rhs) const
       { return lhs.kind < rhs.kind; }
    };
};


void projection_psuedolegal_moves(Piece piece, Vec projection, MoveSet &piece_valid_moves)
// Pass a reference to the valid moves and this function will fill it up!
{
    Position landed_on(piece.position.i, piece.position.j);

    for (int i = 0; i < piece.distance; ++i)
    {
        // Set up the step amount from the increment
        int step = i + 1;
        Vec move_by = projection * step;
        
        // Get the end location and break if it is invalid
        Position landed_on = piece.position + move_by;
        _BREAKIF(!landed_on.is_valid())
        
        // Store the location if it is valid!
        piece_valid_moves.push_back(landed_on);
    }
};

MoveSet piece_psuedolegal_moves(Piece &piece)
// Constructs a list of psuedolegal moves for a given piece and returns it.
{
    const Position& start = piece.position;
    Vec ini_proj = piece.projections[0];
    std::vector<Position> piece_moves;
    
    for (auto &projection : piece.projections)
    { projection_psuedolegal_moves(piece, projection, piece_moves); };

    return piece_moves;
};

MovesMap psuedolegal_moves(std::vector<Piece> &pieces)
{
    std::map<Piece, MoveSet> results;
    for (auto piece : pieces)
    {
        MoveSet piece_moves = piece_psuedolegal_moves(piece);
        results[piece] = piece_moves;
        Log(&piece);
    };
    return results;
};

Allowedtype allowed_move(Position pos, Piece piece)
{
    return AT_disallowed;
}

int main()
{
    // Queen at 4,4 should have 27 moves on an empty board.
    Piece queen = Piecedef::Queen(C_WHITE, Position(4, 4));
    Log(&queen);
    std::vector<Position> moves = piece_psuedolegal_moves(queen);
    assert(moves.size() == 27);
    
    // Knight at 4, 4 should have 8 moves
    Piece knight = Piecedef::Knight(C_WHITE, Position(4, 4));
    Log(&knight);
    std::vector<Position> n_moves = piece_psuedolegal_moves(knight);
    assert(n_moves.size() == 8);
    for (auto i : n_moves)
    {
        Log(&i);
    }
    
    std::vector<Piece> piecelist;
    piecelist.push_back(queen);
    piecelist.push_back(knight);

    MovesMap movemap = psuedolegal_moves(piecelist);
    MovesMap::iterator it = movemap.begin();
    while (it != movemap.end())
    {
        Log(&(it->first));
        Log(&(it->second));
        ++it;
    }
}
