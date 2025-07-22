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

    // since MoveGenerator and GameStateChecker need each other, 
    // they have to be declared as pointers (references can't be null).
    std::unique_ptr<MoveGenerator> moveGenerator;
    std::unique_ptr<GameStateChecker> gameStateChecker;
  
  public:
    BoardManager();

    void init(); // init board to default position (deallocate old data, allocate new)

    // accessors.
    ChessBoard &getBoard();
    MoveMaker &getMoveMaker();

    MoveGenerator *getMoveGenerator();
    GameStateChecker *getGameStateChecker();
};

#endif
