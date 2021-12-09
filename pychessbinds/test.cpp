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
#include "move_analyser.hpp"

#define LOG(x) std::cout << x << std::endl;

#include <map>
#include <array>
#include <vector>

// Can be moved into header
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


int main()
{
    // Define some pieces 
    PieceVec piece_list = {
        Piecedef::Pawn(C_BLACK, Position(6, 4)),
        Piecedef::Pawn(C_WHITE, Position(1, 4))
    };
    
    MoveAnalyser move_analyser(piece_list);
    std::map<Piece, Result> moves =  move_analyser.PsuedolegalMoves(C_WHITE);
    for (auto const& i : moves)
    {
        Log(&i.first);
        Log(&i.first.projections);
        MoveSet passives = i.second.passives;
        Log(&passives);
    }
    
}
