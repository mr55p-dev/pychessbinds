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
    AT_attacks
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


//struct Result
//{
//    MoveSet passives;
//    MoveSet captures;
//    MoveSet attacks;
//    MoveSet defends;
//    MoveSet pins;
//};

typedef std::map<int, MoveSet> Result;

class MoveAnalyser
{
public:
    MoveAnalyser(const PieceVec& pieces);
    
public:
    std::map<Piece, Result> PsuedolegalMoves(const bool colour);
    Allowedtype AllowedMove(const Position* landed_on, const Piece* piece);
    
private:
    PieceVec m_pieces;
    MoveSet m_piece_locations;
    Result PiecePsuedolegalMoves(const Piece* piece);
    void ProjectionPsuedolegalMoves(const Piece* piece, const Vec projection, Result* piece_valid_moves);
    
    
};


