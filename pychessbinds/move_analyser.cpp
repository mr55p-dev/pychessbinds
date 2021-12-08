//
//  move_analyser.cpp
//  pychessbinds
//
//  Created by Ellis Lunnon on 08/12/2021.
//

#include "move_analyser.hpp"
#define _BREAK_ON_PIN if (pinned) {break;};


// Define the constructor
MoveAnalyser::MoveAnalyser(const PieceVec& pieces) : m_pieces(pieces)
{
    
    for (auto piece : pieces)
    {
        m_piece_locations.push_back(piece.position);
    };
}


// Get all the psuedolegal moves for each piece
std::map<Piece, PieceMovesByCat> MoveAnalyser::PsuedolegalMoves()
{
    std::map<Piece, PieceMovesByCat> all_moves;
    
    for (Piece piece : this->m_pieces)
    {
        Log(&piece);
        PieceMovesByCat result = this->PiecePsuedolegalMoves(&piece);
        all_moves.insert({ piece, result});
    }
    return all_moves;
}


// Check all projections for a given piece
PieceMovesByCat MoveAnalyser::PiecePsuedolegalMoves(const Piece* piece)
{
    // Change this for an instance of PieceMovesByCat
    PieceMovesByCat* piece_moves = new PieceMovesByCat;
    for (Vec projection : piece->projections)
    {
        Log(&projection);
        this->ProjectionPsuedolegalMoves(piece, projection, piece_moves);
    };
    return *piece_moves;
};

// For a given projection,
void MoveAnalyser::ProjectionPsuedolegalMoves(
                                              const Piece* piece,
                                              const Vec projection,
                                              PieceMovesByCat* piece_valid_moves)
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
                Log("Empty");
                Log(&landed_on);
                
                _BREAK_ON_PIN;
                if (piece->kind != 'p') {piece_valid_moves->attacks.push_back(landed_on);};
                piece_valid_moves->passives.push_back(landed_on);
                break;
            case AT_capture:
                Log("Capture");
                Log(&landed_on);
                
                _BREAK_ON_PIN;
                piece_valid_moves->captures.push_back(landed_on);
                piece_valid_moves->attacks.push_back(landed_on);
                
                // Set pinned to the landed on position
                pinned = Position(landed_on.i, landed_on.j);
                break;
            case AT_attacks:
                Log("Attack");
                Log(&landed_on);
                
                _BREAK_ON_PIN;
                // Do not continue looking
                piece_valid_moves->attacks.push_back(landed_on);
                quit = true;
                break;
            case AT_checking_attack:
                Log("Checking attack");
                Log(&landed_on);
                
                if (pinned) { piece_valid_moves->pins.push_back(*pinned); }
                else { piece_valid_moves->captures.push_back(landed_on); }
                quit = true;
                break;
            case AT_blocked:
                Log("Blocked");
                Log(&landed_on);
                
                quit = true;
                _BREAK_ON_PIN;
                
                piece_valid_moves->defends.push_back(landed_on);
                break;
            case AT_disallowed:
                Log("Disallowed");
                Log(&landed_on);
                
                quit = true;
        };
    }
};


// Check a move is allowed
Allowedtype MoveAnalyser::AllowedMove(const Position* landed_on, const Piece* piece)
{
    bool capture_allowed = true;
    bool passive_allowed = true;
    
    // Setup pawn validation
    if (piece->kind == 'p')
    {
        int start;
        (piece->colour) ?
            start = 1 :
            start = 6;
        if (piece->position.j - landed_on->j) { passive_allowed = false; }
        else { capture_allowed = false; }
        if (start - piece->position.i && abs(piece->position.j - landed_on->j) == 2)
        { return AT_disallowed; };
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
        else if (capture_allowed) {return AT_attacks; }
        else { return AT_disallowed; };
    } else if (occupier->colour == piece->colour && capture_allowed)
    {
        return AT_blocked;
    } else
    {
        if (capture_allowed && occupier->kind == 'k') { return AT_checking_attack; }
        else if (capture_allowed) { return AT_capture; };
    }
    return AT_disallowed;
}
