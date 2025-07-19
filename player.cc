#include "player.h"
#include "structs.h"

////////////////////////////////////////////////////////////

Player::Player(BoardManager &bm): boardManager{bm} {}
Player::~Player() {}

////////////////////////////////////////////////////////////

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
                    // todo: add input for promotion
                }
            }
        } else if (cmd == "resign") {
            throw RESIGN_ERROR;
        }
    }
}

////////////////////////////////////////////////////////////

Computer::Computer(BoardManager &bm, int level): Player{bm}, level{level} {}
