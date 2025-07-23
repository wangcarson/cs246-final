#include "player-engine.h"
#include "evaluation.h"

Engine::Engine(BoardManager &bm): bm{bm} {}

// white moves maximize eval
int Engine::maxi(int depth) const {
    if (depth == 0) return getEvaluationValue(bm.getBoard());

    auto legalMoves = bm.getMoveGenerator().generateLegalMoves(Colour::White);
    if (legalMoves.empty()) { // white has no moves
        if (bm.getGameStateChecker().isCheck(Colour::White)) return -MAX_EVAL;
        else return 0;
    }

    int max = -MAX_EVAL;
    for (auto move : legalMoves) {
        bm.getMoveMaker().makeMove(move);
        int score = mini(depth - 1);
        if (score > max) max = score;
        bm.getMoveMaker().undoMove();
    }
    return max;
}

// black moves minimize eval (most negative)
int Engine::mini(int depth) const {
    if (depth == 0) return getEvaluationValue(bm.getBoard());

    auto legalMoves = bm.getMoveGenerator().generateLegalMoves(Colour::Black);
    if (legalMoves.empty()) { // black has no moves
        if (bm.getGameStateChecker().isCheck(Colour::Black)) return MAX_EVAL;
        else return 0;
    }

    int min = MAX_EVAL;
    for (auto move : legalMoves) {
        bm.getMoveMaker().makeMove(move);
        int score = maxi(depth - 1);
        if (score < min) min = score;
        bm.getMoveMaker().undoMove();
    }
    return min;
}

Move Engine::getLegalMove(const std::vector<Move> &legalMoves) const {
    Colour c = legalMoves.at(0).getColour(); // should never throw
    
    int bestScore = (c == Colour::White) ? -MAX_EVAL : MAX_EVAL;
    Move bestMove;
    for (auto move : legalMoves) {
        bm.getMoveMaker().makeMove(move);
        if (c == Colour::White) {
            int score = mini(max_depth);
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        } else {
            int score = maxi(max_depth);
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
        bm.getMoveMaker().undoMove();
    }
    return bestMove;
}
