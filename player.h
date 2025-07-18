#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include "structs.h"
#include "boardManager.h"

class Player {
protected:
    BoardManager boardManager;

public:
    Player(BoardManager &bm);
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

// implementation
Player::Player(BoardManager &bm): boardManager{bm} {}
Computer::Computer(BoardManager &bm, int level): Player{bm}, level{level} {}
Human::Human(BoardManager &bm, std::istream &input): Player{bm}, in{input} {}

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
            auto moves = boardManager.getMoveGenerator().generateLegalMoves(boardManager.getMoveMaker().getTurn());
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
