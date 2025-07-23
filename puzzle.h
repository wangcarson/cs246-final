#ifndef __PUZZLE_H__
#define __PUZZLE_H__
#include "structs.h"
#include <vector>
#include <fstream>

class Puzzle {
    std::string fileName = "puzzle.txt";
    std::ifstream inFile;

  public:
    Puzzle();
    std::string getPosition();
    Move getResponseMove(std::vector<Move> &legalMoves);
    bool isCorrectMove(Move inputMove);
};

#endif
