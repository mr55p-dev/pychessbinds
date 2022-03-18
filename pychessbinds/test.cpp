/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


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

//    MoveAnalyser move_analyser(piece_list);
//    std::map<Piece, Result> moves =  move_analyser.PsuedolegalMoves(C_BLACK);

    
    Piece b_queen = Piecedef::Queen(C_BLACK, Position(2, 7));
    Piece b_king = Piecedef::King(C_BLACK, Position(7, 7));
    Piece b_pawn = Piecedef::Pawn(C_BLACK, Position(3, 7));
    Piece w_rook = Piecedef::Rook(C_WHITE, Position(0, 7));
    PieceVec p_list = {b_king, b_queen, b_pawn, w_rook};
    
    MoveAnalyser mal(p_list, std::nullopt);
    
    std::map<Piece, Result> moves = mal.PsuedolegalMoves(C_WHITE);
//    Result q_moves = moves[b_queen];
//    MoveSet passives =
//    Log(&q_moves);
    std::cout << b_queen.position.i << std::endl;
    for (auto const& i : moves)
    {
        Log(&i.first);
//        Log(&i.first.projections);
        auto x = i.second;
        MoveSet passives = x[1];
        MoveSet captures = x[2];
        MoveSet attack = x[3];
        MoveSet defends = x[4];
        MoveSet pins = x[5];
        Log("Passives:");
        Log(&passives);

        Log("Captures:");
        Log(&captures);

        Log("Attacks:");
        Log(&attack);
        
        Log("Defends:");
        Log(&defends);
        
        Log("Pins:");
        Log(&pins);
    }
    
}
