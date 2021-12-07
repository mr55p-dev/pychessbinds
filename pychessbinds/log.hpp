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
