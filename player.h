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
    Board *board; // maybe change to ref?

public:
    Player(Board *b);
    virtual Move getLegalMove() = 0;
};

class Human: public Player {
    std::istream &in;

public:
    Human(Board *b, std::istream &input);
    Move getLegalMove() override;
}; 

class Computer: public Player {
    int level;  

public:
    Computer(Board *b, int level);
    Move getLegalMove() override;
};

// implementation
Player::Player(Board *b): board{b} {}
Computer::Computer(Board *b, int level): Player{b}, level{level} {}
Human::Human(Board *b, std::istream &input): Player{b}, in{input} {}

// Returns a valid move.
Move Human::getLegalMove() {
    std::string cmd;
    in >> cmd;
    if (in.fail()) throw EOF_ERROR; // raise exception

    while (true) {
        if (cmd == "move") {
            string from, to, promote;
            in >> from >> to;
            Tile start, end;
            try {
                start = parseTile(from); // add exception handling here
                end = parseTile(to);
            } catch (int n) {
                cerr << "Invalid tile inputs." << endl;
                continue;
            }
            auto moves = board->generateLegalMoves(board->getTurn());
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
