#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <vector>

#include "move.h"

#include "player.h"
#include "boardmanager.h"

class Computer: public Player {
    int level;
    BoardManager &bm;

    Move getRandomMove(const std::vector<Move> &legalMoves) const;
    Move getL2Move(const std::vector<Move> &legalMoves) const;
    Move getL3Move(const std::vector<Move> &legalMoves) const;

  public:
    Computer(int level, BoardManager &bm);
    Move getLegalMove(const std::vector<Move> &legalMoves) const override;
};

#endif