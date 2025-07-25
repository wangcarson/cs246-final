#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <vector>

#include "move.h"

#include "player.h"
#include "boardmanager.h"

// abstract Computer class 
class Computer: public Player { // getMove() is still abstract
  protected:
    BoardManager &bm;
    Move getRandomMove(const std::vector<Move> &legalMoves) const;
  public:
    Computer(BoardManager &bm);
};

// level 1 computer: random move.
class ComputerL1: public Computer {
    Move getMove(const std::vector<Move> &legalMoves) const override;
  public:
    ComputerL1(BoardManager &bm);
};

// level 2 computer: random capture or check move.
class ComputerL2: public Computer {
    Move getMove(const std::vector<Move> &legalMoves) const override;
  public:
    ComputerL2(BoardManager &bm);
};

// level 3 computer: random capture, check, or "safe" move.
class ComputerL3: public Computer {
    Move getMove(const std::vector<Move> &legalMoves) const override;
  public:
    ComputerL3(BoardManager &bm);
};


#endif
