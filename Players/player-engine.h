#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <vector>

#include "piece.h"
#include "move.h"

#include "player.h"
#include "boardmanager.h"

class Engine: public Player {
    int max_depth = 3; // around 10,000 moves
    BoardManager &bm;

    int alphaBeta(int depth, int alpha, int beta, Colour c) const;

  public:
    Engine(BoardManager &bm);
    Move getMove(const std::vector<Move> &legalMoves) const override;
};

#endif
