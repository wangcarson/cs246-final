#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include "structs.h"
#include "chessBoard.h"
#include "moveMaker.h"
#include "gameStateChecker.h"
#include "moveGenerator.h"

class BoardManager {
    ChessBoard board;
    BoardState boardState;
    GameStateChecker gameStateChecker;
    MoveMaker moveMaker;
    MoveGenerator moveGenerator;
  
  public:
    BoardManager();

    void init(); // init board to default position (deallocate old data, allocate new)

    // accesors.
    ChessBoard getBoard();
    BoardState getBoardState();
    GameStateChecker getGameStateChecker();
    MoveMaker getMoveMaker();
    MoveGenerator getMoveGenerator();
};

#endif
