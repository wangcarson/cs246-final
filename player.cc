#include "player.h"
#include "structs.h"
using namespace std;

////////////////////////////////////////////////////////////

Player::Player(BoardManager &bm): boardManager{bm} {}
Player::~Player() {}

////////////////////////////////////////////////////////////

Human::Human(BoardManager &bm, istream &input): Player{bm}, in{input} {}

// Returns a valid move.
Move Human::getLegalMove() {
    string cmd;
    if (in.fail()) throw eof_error(); // raise exception

    while (true) {
        in >> cmd;
        if (cmd == "move") {
            string from, to, promote;
            in >> from >> to;
            Tile start, end;
            try {
                start = parseTile(from); // add exception handling here
                end = parseTile(to);
            } catch (invalid_argument &r) {
                cerr << r.what() << endl;
                continue;
            }

            auto moves = boardManager.getMoveGenerator().generateLegalMoves(boardManager.getMoveMaker().getTurn());
            for (auto it : moves) {
                if (it.getTo() == start && it.getFrom() == end) {
                    cerr << "Legal move!" << endl;
                    return it;
                    // todo: add input for promotion
                }
            }
            cerr << "Illegal move." << endl;

        } else if (cmd == "resign") {
            throw resign_error();
        }
    }
}

////////////////////////////////////////////////////////////

Computer::Computer(BoardManager &bm, int level): Player{bm}, level{level} {}
Move Computer::getLegalMove() {
    // Actual implementation of bot goes here
    return Move();
}
