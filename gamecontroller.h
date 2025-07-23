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

// The Mode enum represents the current mode of the GameController:
// - Setup Mode is for when we are setting up a position.
// - Game Mode is for taking move commands from input
// - Normal Mode is defult before we choose what other mode we want to be in.
enum class Mode { Setup, Game, Normal };

// implementation included as well (remove later)
// for input and output (maybe change this)
class GameController {
    int turnNumber = 1;
    bool debug = false;
    Mode mode = Mode::Normal;

    BoardManager boardManager;
    
    TextDisplay *td;
    // GraphicsDisplay gd;

    Player *whitePlayer; // only set when 'game' cmd is run (so can't be reference)
    Player *blackPlayer; // don't change to unique_ptr yet

    int whiteScore = 0; // TODO: Change to map
    int blackScore = 0;

    // private helper functions
    Player *getPlayer(std::string s);
    void restart();

  public:
    GameController(bool debug);
    ~GameController();
    void debugBoard(const std::vector<Move> &moves);
    void start();
};

#endif
