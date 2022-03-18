/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


//
//  move_analyser.hpp
//  pychessbinds
//
//  Created by Ellis Lunnon on 08/12/2021.
//
#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include <map>

#include "piece.hpp"
#include "position.hpp"

#define _BREAKIF(cond) if (cond) {break;};
#define C_WHITE 1
#define C_BLACK 0

typedef std::vector<Piece> PieceVec;

enum Allowedtype
{
    AT_empty,
    AT_blocked,
    AT_checking_attack,
    AT_capture,
    AT_disallowed,
    AT_attacks,
    AT_enpassant
};

class ResultKeys
{
public:
    // Copied out of python
    static int passive;
    static int capture;
    static int attack;
    static int defend;
    static int pin;
};


typedef std::map<int, MoveSet> Result;

class MoveAnalyser
{
public:
    MoveAnalyser(const PieceVec& pieces, const std::optional<Position> ep_square = std::nullopt);
    
public:
    std::map<Piece, Result> PsuedolegalMoves(const bool colour);
    Allowedtype AllowedMove(const Position* landed_on, const Piece* piece);
    
private:
    PieceVec m_pieces;
    MoveSet m_piece_locations;
    const std::optional<Position> m_ep_square;
    Result PiecePsuedolegalMoves(const Piece* piece);
    void ProjectionPsuedolegalMoves(const Piece* piece, const Vec projection, Result* piece_valid_moves);
    
    
};


