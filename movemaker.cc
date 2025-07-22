#include "movemaker.h"
using namespace std;

MoveMaker::MoveMaker(ChessBoard &b): board{b} { initBoardState(); }

void MoveMaker::initBoardState() {
    turn = Colour::White;
    enPassant = std::nullopt;
    whiteCastleQueen = true;
    whiteCastleKing = true;
    blackCastleQueen = true;
    blackCastleKing = true;
}

// assumes m is a legal move
void MoveMaker::makeMove(Move m) {
    BoardState b{turn, enPassant, whiteCastleQueen, whiteCastleKing, blackCastleQueen, blackCastleKing};
    previous.emplace_back(MoveData{m, b});

    // add and remove pieces.
    board.removePiece(m.getFrom());
    if (m.isPromotion()) {
        board.setPiece(m.getTo(), m.getPromotionPiece());
    } else {
        board.setPiece(m.getTo(), m.getPiece());
    }

    // special cases.
    auto [r, c] = m.getFrom();
    auto [nr, nc] = m.getTo();
    if (m.isCastle()) {
        Tile oldRookTile = c < nc ? Tile{r, 7} : Tile{r, 1};
        Tile newRookTile{r, (c+nc)/2};
        board.removePiece(oldRookTile);
        board.setPiece(newRookTile, Piece{PieceType::Rook, turn});
    } else if (m.isEnPassant()) {
        Tile captureTile{r, nc};
        board.removePiece(captureTile);
    }

    // castling and en passant states.
    if (m.getPiece().isRook() || m.getPiece().isKing()) {
        if (turn == Colour::White) {
            whiteCastleKing = false;
            whiteCastleQueen = false;
        } else {
            blackCastleKing = false;
            blackCastleQueen = false;
        }
    }
    if (m.isDoubleAdvance()) {
        enPassant = m.getTo();
    } else {
        enPassant = nullopt;
    }

    // change turn
    turn = turn == Colour::White ? Colour::Black : Colour::White;
}

void MoveMaker::undoMove() {
    if (previous.size() == 0) return;
    // set previous state to current state
    // move piece back
    // revert captured pieces
    // change turn
}

// board state accessors.
Colour MoveMaker::getTurn() { return turn; }
std::optional<Tile> MoveMaker::getEnPassant() { return enPassant; }
bool MoveMaker::getCastlingRights(Colour c, bool kside) {
    if (c == Colour::White) {
        return kside ? whiteCastleKing : whiteCastleQueen;
    } else {
        return kside ? blackCastleKing : blackCastleQueen;
    }
}

// board state mutators.
void MoveMaker::setTurn(Colour c) { turn = c; }
void MoveMaker::setEnPassant(std::optional<Tile> t) { enPassant = t; }
void MoveMaker::setCastlingRights(Colour c, bool kside, bool b) {
    // TODO
}
