#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include <structs.h>

class Player {
  public:
    virtual Move getMove() = 0;
};

class Human: public Player {
    std::istream &input;

  public:
    Human(std::istream &input);
    Move getMove() override;
}; 

class Computer: public Player {
    int level;
    std::vector<std::vector<std::optional<Piece>>> &board;
    // private methods for computation.
  
  public:
    Computer(int level, std::vector<std::vector<std::optional<Piece>>> &grid);
    Move getMove() override;
};


Move Human::getMove() {
    std::string cmd;
    cin >> cmd;
    if (cin.fail()) throw 0; // raise exception

    if (cmd == "move") {
        string s, e, promote;
        cin >> s >> e;

        // parse input and create moves
        // Tile startTile = parseTile(s); // add exception here
        // Tile endTile = parseTile(e);

        // Move m{MoveType::Unknown, startTile, endTile};

    } else if (cmd == "resign") {
        // endGame();

    }
}
