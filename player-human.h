#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <vector>
#include <iostream>

#include "structs.h"
#include "player.h"

class Human: public Player {
    std::istream &in;
    Colour color;
  public:
    Human(std::istream &input, Colour color);
    Move getLegalMove(const std::vector<Move> &legalMoves) const override;
}; 

#endif