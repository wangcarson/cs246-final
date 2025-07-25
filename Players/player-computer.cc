#include "player-computer.h"
#include <iostream>

#include <ctime>
#include <cstdlib>
using namespace std;

Computer::Computer(BoardManager &bm): bm{bm} { srand(time(0)); } // seed RNG 

// method for getting random move.
// Invariant: legalMoves.size() > 0
// Should be enforced by isValidBoard() and checkmate + stalemate checks
Move Computer::getRandomMove(const vector<Move> &moves) const {
    int n = moves.size();
    if (n == 0) throw exception();
    return moves.at(rand() % n);
}

// level 1 computer: random move.
ComputerL1::ComputerL1(BoardManager &bm): Computer{bm} {}
Move ComputerL1::getMove(const vector<Move> &legalMoves) const {
    Move m = getRandomMove(legalMoves);
    cout << "Computer move: " << m << endl;
    return m;
}

// level 2 computer: random capture or check move.
ComputerL2::ComputerL2(BoardManager &bm): Computer{bm} {}
Move ComputerL2::getMove(const vector<Move> &legalMoves) const {
    vector<Move> moves;
    for (auto m : legalMoves) {
        if (m.isCapture() || bm.getMoveGenerator().isCheckMove(m)) { 
            moves.emplace_back(m);
        }
    }
    Move m = moves.empty() ? getRandomMove(legalMoves) : getRandomMove(moves);
    cout << "Computer move: " << m << endl;
    return m;
}

// level 3 computer: random capture, check, or "safe" move.
ComputerL3::ComputerL3(BoardManager &bm): Computer{bm} {}
Move ComputerL3::getMove(const vector<Move> &legalMoves) const {
    vector<Move> moves;
    for (auto m : legalMoves) {
        if (m.isCapture() || bm.getMoveGenerator().isCheckMove(m) || bm.getMoveGenerator().isSafeMove(m)) {
            moves.emplace_back(m);
        }
    }
    Move m = moves.empty() ? getRandomMove(legalMoves) : getRandomMove(moves);
    cout << "Computer move: " << m << endl;
    return m;
}


