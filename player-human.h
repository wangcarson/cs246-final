#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <vector>
#include <iostream>

#include "structs.h"
#include "player.h"

class Human: public Player {
    std::istream &in;

  public:
    Human(std::istream &input);
    Move getLegalMove(const std::vector<Move> &moves) const override;
}; 

#endif