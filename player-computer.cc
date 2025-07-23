#include "player-computer.h"
#include <iostream>

#include <ctime>
#include <cstdlib>
using namespace std;

Computer::Computer(int level): level{level} { srand(time(0)); } // seed RNG 

Move Computer::getLegalMove(const vector<Move> &legalMoves) const {
    // TODO: Actual implementation of bot goes here
    // Maybe make a different class for each type of bot
    int n = legalMoves.size();
    Move move = legalMoves.at(rand() % n);
    cout << "Computer move: " << move << endl;
    return move;
}

