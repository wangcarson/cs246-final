#include "evaluation.h"

int getPieceValue(Piece p) {
    int n = static_cast<int>(p.colour);
    switch (p.type) {
        case PieceType::Pawn:   return n*100;
        case PieceType::Knight: return n*320;
        case PieceType::Bishop: return n*330;
        case PieceType::Rook:   return n*500;
        case PieceType::Queen:  return n*900;
        case PieceType::King:   return n*20000;
        default:                return 0;
    }
};

int getPositionValue(Piece p, Tile t) {
    int n = static_cast<int>(p.colour);
    if (p.colour == Colour::White) {
        t.row = BOARD_ROWS-t.row-1;
    }
    int i = t.row*BOARD_COLS + t.col;
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

int getEvaluationValue(ChessBoard &b) {
    int eval = 0;
    for (int i = 0; i < BOARD_ROWS; ++i) {
        for (int j = 0; j < BOARD_COLS; ++j) {
            Tile t{i, j};
            Piece p = b.getPiece(t);
            eval += getPieceValue(p);
            eval += getPositionValue(p, t);
        }
    }
    return eval;
}
