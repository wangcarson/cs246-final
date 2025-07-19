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
    BoardManager boardManager;

public:
    Player(BoardManager &bm);
    virtual ~Player();
    virtual Move getLegalMove() = 0;
};

class Human: public Player {
    std::istream &in;

  public:
    Human(BoardManager &bm, std::istream &input);
    Move getLegalMove() override;
}; 

class Computer: public Player {
    int level;  

  public:
    Computer(BoardManager &bm, int level);
    Move getLegalMove() override;
};

#endif
