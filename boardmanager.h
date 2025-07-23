#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include <memory>

#include "structs.h"
#include "chessboard.h"
#include "movemaker.h"
#include "gamestatechecker.h"
#include "movegenerator.h"

class BoardManager {
    ChessBoard board;
    MoveMaker moveMaker;
    MoveGenerator moveGenerator;
    GameStateChecker gameStateChecker;
  
  public:
    BoardManager();

    void init(); // init board and state to defaults

    // accessors.
    ChessBoard &getBoard();
    MoveMaker &getMoveMaker();
    MoveGenerator &getMoveGenerator();
    GameStateChecker &getGameStateChecker();
};

#endif
