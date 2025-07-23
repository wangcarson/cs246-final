#ifndef __PUZZLE_H__
#define __PUZZLE_H__
#include "structs.h"
#include <vector>
#include <fstream>

class Puzzle{

    string fileName = "puzzle.txt";

    public:

        Move getResponseMove(std::vector<Move> &legalMoves);
        std::string getfileInput();
        bool isCorrectMove(Move inputMove);

    
};

#endif
