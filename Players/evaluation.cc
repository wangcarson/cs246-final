#include "evaluation.h"

int getPieceValue(Piece p) {
    int n = static_cast<int>(p.colour);
    switch (p.type) {
        case PieceType::Pawn:   return n*82;
        case PieceType::Knight: return n*337;
        case PieceType::Bishop: return n*365;
        case PieceType::Rook:   return n*477;
        case PieceType::Queen:  return n*1025;
        case PieceType::King:   return n*20000;
        default:                return 0;
    }
};

int getPositionValue(Piece p, Tile t) {
    int n = static_cast<int>(p.colour);
    if (p.colour == Colour::White) {
        t.row = BOARD_SIZE-t.row-1;
    }
    int i = t.row*BOARD_SIZE + t.col;
    switch (p.type) {
        case PieceType::Pawn:   return n*PAWN_VALUES[i];
        case PieceType::Knight: return n*KNIGHT_VALUES[i];
        case PieceType::Bishop: return n*BISHOP_VALUES[i];
        case PieceType::Rook:   return n*ROOK_VALUES[i];
        case PieceType::Queen:  return n*QUEEN_VALUES[i];
        case PieceType::King:   return n*KING_VALUES[i];
        default:                return 0;
    }
}

// positive for how good position is the current player is.
int getEvaluationValue(BoardManager &b) {
    int n = static_cast<int>(b.getMoveMaker().getTurn());
    int eval = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Tile t{i, j};
            Piece p = b.getBoard().getPiece(t);
            eval += getPieceValue(p);
            eval += getPositionValue(p, t);
        }
    }
    return n*eval;
}
