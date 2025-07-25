#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>

#include "move.h"

// abstract Player class 
class Player {
    // Returns a legal move. Overrided by subclasses.
    virtual Move getMove(const std::vector<Move> &legalMoves) const = 0;

  public:
    virtual ~Player() = default;
    Move getLegalMove(const std::vector<Move> &legalMoves) { return getMove(legalMoves); }
};

#endif
