#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>

#include "structs.h"

class Player {
  public:
    // No fields, so we use default ctors.

    // Returns a legal move. Overrided by subclasses.
    virtual Move getLegalMove(const std::vector<Move> &moves) const = 0;
};

#endif
