#ifndef __PUZZLE_H__
#define __PUZZLE_H__
#include "structs.h"
#include <fstream>

class Puzzle{

    fstream puzzleFile {"puzzle.txt"};

    public:

        
        std::string getPosition();
        std::string getResponse();
        bool isCorrectMove(Move inputMove);

    
};

#endif
