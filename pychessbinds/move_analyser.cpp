//
//  move_analyser.cpp
//  pychessbinds
//
//  Created by Ellis Lunnon on 08/12/2021.
//

#include "move_analyser.hpp"

#define _BREAK_ON_PIN if (pinned) { quit = true; break; };

int ResultKeys::passive = 1;
int ResultKeys::capture = 2;
int ResultKeys::attack = 3;
int ResultKeys::defend = 4;
int ResultKeys::pin = 5;


// Define the constructor
MoveAnalyser::MoveAnalyser(const PieceVec& pieces, const std::optional<Position> ep_square)
    : m_pieces(pieces), m_ep_square(ep_square)
{
    for (auto piece : pieces)
    {
        m_piece_locations.push_back(piece.position);
    };
}


// Get all the psuedolegal moves for each piece
std::map<Piece, Result> MoveAnalyser::PsuedolegalMoves(const bool colour)
{
    std::map<Piece, Result> all_moves;
    
    for (Piece piece : this->m_pieces)
    {
        // Skip if the piece is the wrong colour
        if (piece.colour != colour) { continue; };
        
        // Analyse the results of our search
        Result result = this->PiecePsuedolegalMoves(&piece);
        all_moves.insert({ piece, result});
    }
    return all_moves;
}


// Check all projections for a given piece
Result MoveAnalyser::PiecePsuedolegalMoves(const Piece* piece)
{
    // Change this for an instance of Result
    Result* piece_moves = new Result;
    (*piece_moves)[1] = MoveSet{};
    (*piece_moves)[2] = MoveSet{};
    (*piece_moves)[3] = MoveSet{};
    (*piece_moves)[4] = MoveSet{};
    (*piece_moves)[5] = MoveSet{};

    for (Vec projection : piece->projections)
    {
        this->ProjectionPsuedolegalMoves(piece, projection, piece_moves);
    };
    return *piece_moves;
};

// For a given projection,
void MoveAnalyser::ProjectionPsuedolegalMoves(
                                              const Piece* piece,
                                              const Vec projection,
                                              Result* piece_valid_moves)
{
    std::optional<Position> pinned = std::nullopt;
    
    bool quit = false;
    for (int i = 0; i < piece->distance && !quit; ++i)
    {
        // Define a variable to break out the loop
        // Define the distance to move from the origin
        int step = i + 1;
        Vec move_by = projection * step;
        
        // Get the square landed on and break if it is invalid
        Position landed_on = piece->position + move_by;
        _BREAKIF(!landed_on.is_valid());
        
        // Check the validity of the move
        Allowedtype allowed = this->AllowedMove(&landed_on, piece);
        switch (allowed) {
            case AT_empty:
                _BREAK_ON_PIN;
                if (piece->kind != 'P') {(*piece_valid_moves)[ResultKeys::attack].push_back(landed_on);};
                (*piece_valid_moves)[ResultKeys::passive].push_back(landed_on);
                break;
            case AT_capture:
                _BREAK_ON_PIN;
                (*piece_valid_moves)[ResultKeys::capture].push_back(landed_on);
                (*piece_valid_moves)[ResultKeys::attack].push_back(landed_on);
                
                // Set pinned to the landed on position
                pinned = Position(landed_on.i, landed_on.j);
                break;
            case AT_attacks:
                _BREAK_ON_PIN;
                // Do not continue looking
                (*piece_valid_moves)[ResultKeys::attack].push_back(landed_on);
                quit = true;
                break;
            case AT_checking_attack:
                if (pinned)
                { (*piece_valid_moves)[ResultKeys::pin].push_back(*pinned); }
                else { (*piece_valid_moves)[ResultKeys::capture].push_back(landed_on); }
                quit = true;
                break;
            case AT_blocked:
                quit = true;
                _BREAK_ON_PIN;
                
                (*piece_valid_moves)[ResultKeys::defend].push_back(landed_on);
                break;
            case AT_enpassant:
                quit = true;
                _BREAK_ON_PIN;
                
                (*piece_valid_moves)[ResultKeys::capture].push_back(landed_on);
                break;
            case AT_disallowed:
                quit = true;
                break;
        };
    }
};


// Check a move is allowed
Allowedtype MoveAnalyser::AllowedMove(const Position* landed_on, const Piece* piece)
{
    bool capture_allowed = true;
    bool passive_allowed = true;
    
    // Setup pawn validation
    if (piece->kind == 'P')
    {
        int start;
        (piece->colour) ?
            start = 1 :
            start = 6;
        if (piece->position.j - landed_on->j)
        {
            passive_allowed = false;
        }
        else
        {
            capture_allowed = false;
        }
        if (start - piece->position.i && abs(piece->position.j - landed_on->j) == 2)
        {
            return AT_disallowed;
        };
    };
    

    // Define properties for the find
    PieceVec::iterator start = std::begin(this->m_pieces);
    PieceVec::iterator end   = std::end(this->m_pieces);
    auto check_position = [landed_on](Piece other){return other.position == *landed_on;};
    
    // Conditionally check if any of the pieces are at the location
    PieceVec::iterator occupier = std::find_if(start, end, check_position);
    
    // Check the result
    if (occupier == end)
    {
        // Not occupied
        if (passive_allowed) { return AT_empty; }
        else if (capture_allowed) { return AT_attacks; }
        // Check if the piece is a pawn, and if m_ep_square is set
        else if (piece->kind == 'P' && *landed_on == m_ep_square) { return AT_enpassant; }
        else { return AT_disallowed; };
    } else if (occupier->colour == piece->colour)
    {
        if (capture_allowed)
        {
            return AT_blocked;
        }
    } else
    {
        if (capture_allowed && occupier->kind == 'K') { return AT_checking_attack; }
        else if (capture_allowed)
        { return AT_capture; };
    }
    return AT_disallowed;
}
