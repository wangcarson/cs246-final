#ifndef __GAMESTATECHECKER_H__
#define __GAMESTATECHECKER_H__

#include "structs.h"
#include "chessboard.h"
#include "movegenerator.h"

class MoveGenerator; // forward declaration

class GameStateChecker {
    ChessBoard &board;
    MoveGenerator *moveGenerator = nullptr;
  
  public:
    GameStateChecker(ChessBoard &b);
    void setMG(MoveGenerator *mg);

    // checking game states.
    bool isValidBoard();    // verify one king each, no pawns on last rank, no checks
    bool isCheck(Colour c); // check
    bool isMate(Colour c);  // checkmate (no moves, check)
    bool isDraw(Colour c);  // stalemate (no moves, no check) or no material
};

#endif
