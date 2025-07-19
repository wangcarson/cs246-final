#ifndef __MOVEGENERATOR_H__
#define __MOVEGENERATOR_H__

#include "structs.h"
#include "chessboard.h"

class MoveGenerator {
    ChessBoard &board;

    // add private functions
    // getPawnMoves(Tile t);
  
  public:
    MoveGenerator(ChessBoard &b);

    // generating moves.
    std::vector<Move> generateLegalMoves(Colour c);
    std::vector<Move> getLegalMoves(Tile t);
};

#endif
