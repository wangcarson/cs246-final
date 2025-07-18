#ifndef __MOVEMAKER_H__
#define __MOVEMAKER_H__
#include <vector>

#include "structs.h"
#include "chessBoard.h"

class MoveMaker: public Subject {
    ChessBoard &board;
    std::vector<BoardState> previous;
  
  public:
    MoveMaker();
  
    // making moves (add to previous)
    bool isLegal(Move m);
    void makeMove(Move m); // should be called on legal moves
    void undoMove();
};

#endif
