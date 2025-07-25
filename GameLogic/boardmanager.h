#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include <memory>
#include <string>


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
    void init(std::string position); // init board and state to defaults
    std::string boardToFen();

    // accessors.
    ChessBoard &getBoard();
    MoveMaker &getMoveMaker();
    MoveGenerator &getMoveGenerator();
    GameStateChecker &getGameStateChecker();

};

#endif
