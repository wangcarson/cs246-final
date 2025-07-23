#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include "structs.h"
#include "boardmanager.h"

class Player {
  protected:
    BoardManager &boardManager;

public:
    Player(BoardManager &bm);
    virtual ~Player();
    virtual Move getLegalMove(const std::vector<Move> &moves) const = 0;
};

class Human: public Player {
    std::istream &in;

  public:
    Human(BoardManager &bm, std::istream &input);
    Move getLegalMove(const std::vector<Move> &moves) const override;
}; 

class Computer: public Player {
    int level;  

  public:
    Computer(BoardManager &bm, int level);
    Move getLegalMove(const std::vector<Move> &moves) const override;
};

#endif
