#include "player-computer.h"
#include <iostream>

#include <ctime>
#include <cstdlib>
using namespace std;

// Invariant: legalMoves.size() > 0
// Should be enforced by isValidBoard() and checkmate + stalemate checks

Computer::Computer(int level, BoardManager &bm): 
    level{level}, bm{bm} { srand(time(0)); } // seed RNG 

// helper function for getting random move.
Move Computer::getRandomMove(const vector<Move> &moves) const {
    int n = moves.size();
    if (n == 0) throw exception();
    return moves.at(rand() % n);
}

Move Computer::getL2Move(const vector<Move> &legalMoves) const {
    vector<Move> moves;
    for (auto m : legalMoves) {
        if (m.isCapture() || bm.getMoveGenerator().isCheckMove(m)) {
            moves.emplace_back(m);
        }
    }
    return getRandomMove(moves);
}

Move Computer::getL3Move(const vector<Move> &legalMoves) const {
    vector<Move> moves;
    for (auto m : legalMoves) {
        if (m.isCapture() || bm.getMoveGenerator().isCheckMove(m) || bm.getMoveGenerator().isSafeMove(m)) {
            moves.emplace_back(m);
        }
    }
    return getRandomMove(moves);
}

Move Computer::getMove(const vector<Move> &legalMoves) const {
    Move m;
    switch (level) {
        case 3:
            try {
                m = getL3Move(legalMoves);
                break;
            } catch (...) {} // throw goes to case 1
        case 2:
            try {
                m = getL2Move(legalMoves);
                break;
            } catch (...) {} // throw goes to case 1
        case 1:
            m = getRandomMove(legalMoves);
            break;
    }
    cout << "Computer move: " << m << endl;
    return m;
}

