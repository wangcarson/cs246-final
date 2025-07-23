#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <vector>

#include "structs.h"
#include "player.h"

class Computer: public Player {
    int level;  

  public:
    Computer(int level);
    Move getLegalMove(const std::vector<Move> &legalMoves) const override;
};

#endif