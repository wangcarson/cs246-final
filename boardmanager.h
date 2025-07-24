#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include <memory>
#include <string>

#include "structs.h"
#include "chessboard.h"
#include "movemaker.h"
#include "gamestatechecker.h"
#include "movegenerator.h"

const std::string DEFAULT_POSITION = "8/PPPP4/5k2/8/8/8/8/K7 w";//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w

class BoardManager {
    ChessBoard board;
    MoveMaker moveMaker;
    MoveGenerator moveGenerator;
    GameStateChecker gameStateChecker;
  
  public:
    BoardManager();
    void init(std::string position=DEFAULT_POSITION); // init board and state to defaults

    // accessors.
    ChessBoard &getBoard();
    MoveMaker &getMoveMaker();
    MoveGenerator &getMoveGenerator();
    GameStateChecker &getGameStateChecker();
};

#endif
