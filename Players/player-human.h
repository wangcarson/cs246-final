#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <vector>
#include <iostream>

#include "piece.h"
#include "move.h"

#include "player.h"

class Human: public Player {
    std::istream &in;
    Colour colour;
  public:
    Human(std::istream &input, Colour colour);
    Move getMove(const std::vector<Move> &legalMoves) const override;
}; 

#endif
