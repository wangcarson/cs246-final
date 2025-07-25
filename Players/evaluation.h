#ifndef __EVALUATION_H__
#define __EVALUATION_H__
#include <map>
#include "piece.h"
#include "boardmanager.h"

// Evaluation values from:
// https://www.chessprogramming.org/Simplified_Evaluation_Function
const int MAX_EVAL = 64000; // approximate

// Evaluation functions.
int getPieceValue(Piece p);
int getPositionValue(Piece p, Tile t);
int getEvaluationValue(BoardManager &);

#endif
