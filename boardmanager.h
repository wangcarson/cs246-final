#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include "structs.h"

#include "chessboard.h"
#include "movemaker.h"
#include "gamestatechecker.h"
#include "movegenerator.h"

class BoardManager {
    ChessBoard board;
    MoveGenerator moveGenerator;
    GameStateChecker gameStateChecker;
    MoveMaker moveMaker;
  
  public:
    BoardManager();

    void init(); // init board to default position (deallocate old data, allocate new)

    // accessors.
    ChessBoard &getBoard();
    GameStateChecker &getGameStateChecker();
    MoveMaker &getMoveMaker();
    MoveGenerator &getMoveGenerator();
};

#endif
