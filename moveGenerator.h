#ifndef __MOVEGENERATOR_H__
#define __MOVEGENERATOR_H__

#include "structs.h"
#include "chessBoard.h"

class MoveGenerator {
    ChessBoard &board;
  
  public:
    MoveGenerator();

    // generating moves.
    std::vector<Move> generateLegalMoves(Colour c);
    std::vector<Move> getLegalMoves(Tile t);
};

#endif
