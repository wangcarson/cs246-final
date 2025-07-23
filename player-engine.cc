#include "player-engine.h"
#include "evaluation.h"
#include <iostream>
using namespace std;

Engine::Engine(BoardManager &bm): bm{bm} {}

// returns negative for better positions
int Engine::alphaBeta(int depth, int alpha, int beta, Colour c) const {
    if (depth == 0) return getEvaluationValue(bm);

    auto legalMoves = bm.getMoveGenerator().generateLegalMoves();
    if (legalMoves.empty()) {
        if (bm.getGameStateChecker().isCheck(bm.getMoveMaker().getTurn())) return -MAX_EVAL;
        else return 0;
    }

    int bestValue = -MAX_EVAL;
    for (auto move : legalMoves)  {
        bm.getMoveMaker().makeMove(move);
        int score = -alphaBeta(depth-1, -beta, -alpha, c);
        bm.getMoveMaker().undoMove();

        if (score > bestValue) {
            bestValue = score;
            if (score > alpha) alpha = score;
        }
        if (score >= beta) return bestValue;
    }
   return bestValue;
}

Move Engine::getLegalMove(const std::vector<Move> &legalMoves) const {
    Colour c = legalMoves.at(0).getColour(); // should never throw
    
    int bestScore = -MAX_EVAL;
    Move bestMove;
    for (const Move &move : legalMoves) {
        bm.getMoveMaker().makeMove(move);
        int score = -alphaBeta(max_depth-1, -MAX_EVAL, MAX_EVAL, c);
        bm.getMoveMaker().undoMove();
        
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    cout << "Engine move: " << bestMove << endl;
    return bestMove;
}
