#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <memory>

#include "structs.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "boardmanager.h"
#include "player.h"

// implementation included as well (remove later)
// for input and output (maybe change this)
class GameController {
    Mode mode;
    BoardManager boardManager;
    
    TextDisplay *td;
    // GraphicsDisplay gd;

    Player *whitePlayer; // only set when 'game' cmd is run
    Player *blackPlayer; // don't change to unique_ptr yet

    int whiteScore = 0;
    int blackScore = 0;

    // private helper functions
    Player *getPlayer(std::string s);
    void restart();

  public:
    GameController();
    ~GameController();
    void debug();
    void start();
};

#endif
