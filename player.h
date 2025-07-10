#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include "structs.h"
#include "board.h"

class Player {
protected:
    Colour colour;
    Board &board;

public:
    Player(Board &b, Colour c);
    virtual Move getLegalMove() = 0;
};

class Human: public Player {
    std::istream &in;

public:
    Human(Board &b, Colour c, std::istream &input);
    Move getLegalMove() override;
}; 

class Computer: public Player {
    int level;  

public:
    Computer(Board &b, Colour c, int level);
    Move getLegalMove() override;
};

// implementation
Player::Player(Board &b, Colour c): board{b}, colour{c} {}
Computer::Computer(Board &b, Colour c, int level): Player{b, c}, level{level} {}
Human::Human(Board &b, Colour c, std::istream &input): Player{b, c}, in{input} {}

// Returns a valid move.
Move Human::getLegalMove() {
    std::string cmd;
    if (in.fail()) throw EOF_ERROR; // raise exception

    while (true) {
        if (cmd == "move") {
            std::string from, to, promote;
            in >> from >> to;
            Tile start, end;
            try {
                start = parseTile(from); // add exception handling here
                end = parseTile(to);
            } catch (int n) {
                std::cerr << "Invalid tile inputs." << std::endl;
                continue;
            }
            auto moves = board.generateLegalMoves(board.getTurn());
            for (auto it : moves) {
                if (it.getTo() == start && it.getFrom() == end) {
                    return it;
                }
            }
        } else if (cmd == "resign") {
            throw RESIGN_ERROR;
        }
    }
}

#endif
