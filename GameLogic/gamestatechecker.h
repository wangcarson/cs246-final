#ifndef __GAMESTATECHECKER_H__
#define __GAMESTATECHECKER_H__
#include "piece.h"

#include "chessboard.h"
#include "movegenerator.h"

class MoveGenerator; // forward declaration

class GameStateChecker {
    ChessBoard &board;
    MoveGenerator &moveGenerator;
  
  public:
    GameStateChecker(ChessBoard &b, MoveGenerator &mg);
    
    // checking game states.
    bool isValidBoard();         // verify one king each, no pawns on last rank, no checks
    bool isCheck(Colour c);      // check
    bool isCheckmate(Colour c);  // checkmate (no moves, check)
    bool isStalemate(Colour c);  // stalemate (no moves, no check) or no material
    bool isMaterialDraw();       // insufficient material
};

#endif
