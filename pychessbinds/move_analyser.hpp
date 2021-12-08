//
//  move_analyser.hpp
//  pychessbinds
//
//  Created by Ellis Lunnon on 08/12/2021.
//
#pragma once

#include <iostream>
#include <optional>
#include <functional>
#include <vector>
#include <map>

#include "piece.hpp"
#include "position.hpp"
#include "test.hpp"
#include "log.hpp"


#define _BREAKIF(cond) if (cond) {break;};

typedef std::vector<Piece> PieceVec;

struct PieceMovesByCat
{
    MoveSet passives;
    MoveSet captures;
    MoveSet attacks;
    MoveSet defends;
    MoveSet pins;
};


class MoveAnalyser
{
public:
    MoveAnalyser(const PieceVec& pieces);
    
public:
    std::map<Piece, PieceMovesByCat> PsuedolegalMoves();
    Allowedtype AllowedMove(const Position* landed_on, const Piece* piece);
    
private:
    PieceVec m_pieces;
    MoveSet m_piece_locations;
    PieceMovesByCat PiecePsuedolegalMoves(const Piece* piece);
    void ProjectionPsuedolegalMoves(const Piece* piece, const Vec projection, PieceMovesByCat* piece_valid_moves);
    
    
};


