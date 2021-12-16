/* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
/* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
/* with any significant material copied or adapted from other sources clearly indicated and attributed. */


//
//  log.hpp
//  PyChessBinds
//
//  Created by Ellis Lunnon on 04/12/2021.
//

#ifndef log_h
#define log_h

#include "piece.hpp"
#include "position.hpp"

void Log(const char* message);
void Log(const Piece* piece);
void Log(const Vec* vec);
void Log(const MoveSet* moveset);
void Log(const Position* pos);
void Log(const ProjectionSet* list);

#endif /* log_h */
