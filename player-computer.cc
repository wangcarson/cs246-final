#include "player-computer.h"
#include <iostream>
using namespace std;

Computer::Computer(int level): level{level} {}
Move Computer::getLegalMove(const vector<Move> &legalMoves) const {
    // TODO: Actual implementation of bot goes here
    // Maybe make a different class for each type of bot

    Move move = legalMoves.at(0);
    cout << "Computer move: " << move << endl;
    return move;
}
