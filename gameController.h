#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <vector>
#include <iostream>
#include <string>
#include <optional>

#include "structs.h"
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "player.h"

// implementation included as well (remove later)
// for input and output (maybe change this)
class GameController {
    Mode mode;
    Board board;

    TextDisplay td;
    GraphicsDisplay gd;

    Player *whitePlayer = nullptr;
    Player *blackPlayer = nullptr;

    int whiteScore = 0;
    int blackScore = 0;

    // private helper functions
    Player *getPlayer(std::string s);
    void restart();

  public:
    GameController();
    ~GameController();
    void start();
};

#endif
