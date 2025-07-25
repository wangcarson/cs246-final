#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>

#include "move.h"


class Player {
  public:
    virtual ~Player() = default;

    // Returns a legal move. Overrided by subclasses.
    virtual Move getLegalMove(const std::vector<Move> &legalMoves) const = 0;
};

#endif
