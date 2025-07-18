#include "moveMaker.h"
using namespace std;

MoveMaker::MoveMaker(ChessBoard &b, GameStateChecker &gsc): board{b}, stateChecker{gsc} { initBoardState(); }

void MoveMaker::initBoardState() {
  turn = Colour::White;
  enPassant = std::nullopt;
  castlingRights = {{Colour::White, true}, {Colour::Black, true}};
}

// making moves (add to previous)
bool MoveMaker::isLegal(Move m) {
    makeMove(m);
    bool legal = !stateChecker.isCheck(m.getColour());
    undoMove();
    return legal;
}

// assumes m is a legal move
void MoveMaker::makeMove(Move m) {
    previous.emplace_back(BoardState{turn, m, enPassant, castlingRights});

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
        castlingRights[turn] = false;
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
bool MoveMaker::getCastlingRights(Colour c, bool kside) { return castlingRights[c]; }

// board state mutators.
void MoveMaker::setTurn(Colour c) { turn = c; }
void MoveMaker::setCastlingRights(Colour c, bool kside, bool b) { castlingRights[c] = b; }
void MoveMaker::setEnPassant(std::optional<Tile> t) { enPassant = t; }
