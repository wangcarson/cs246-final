#ifndef __PUZZLE_H__
#define __PUZZLE_H__
#include "structs.h"
#include <vector>
#include <fstream>

class Puzzle {
    int puzzleLineNumber=1;
    std::string fileName;
    std::ifstream inFile;
    
    Tile correctStart;
    Tile correctEnd;
    Tile responseStart;
    Tile responseEnd;

  public:

    Puzzle(std::string fileName="puzzle.txt");
    std::string getPosition();
    Move getResponseMove(std::vector<Move> &legalMoves);
    bool isCorrectMove(Move inputMove);
    void loadMoves();

};

#endif
