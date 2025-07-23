#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "structs.h"
#include "puzzle.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "boardmanager.h"
#include "player.h"

// The Mode enum represents the current mode of the GameController:
// - Setup Mode is for when we are setting up a position.
// - Game Mode is for taking move commands from input
// - Normal Mode is defult before we choose what other mode we want to be in.
enum class Mode { Setup, Game, Normal, Puzzle };

// implementation included as well (remove later)
// for input and output (maybe change this)
class GameController {
    BoardManager boardManager;

    std::istream &in;
    std::unique_ptr<TextDisplay> td;
    // GraphicsDisplay gd;

    Mode mode = Mode::Normal;
    int turnNumber = 1;
    bool debug = false;

    // Maps for player objects and scores.
    std::map<Colour, std::unique_ptr<Player>> players;
    std::map<Colour, float> scores;
    // Players are null until the 'game' cmd is run (so must be pointers)

    // Puzzle objects.
    std::unique_ptr<Player> puzzlePlayer;
    std::unique_ptr<Puzzle> puzzle;

    // Creates a Player object corresponding to string `s`.
    // Returns as a smart pointer (transfers ownership).
    std::unique_ptr<Player> getPlayer(std::string s,Colour c);

    // Restarts the game by resetting states.
    void resetState();

    // Private method for debugging only (prints board info).
    void printData(const std::vector<Move> &moves);

  public:
    GameController(std::istream &in, bool debug);

    // Main function for controlling the program. Should be called by `main()`.
    // Manages input and error handling.
    void runGame();
};

#endif
