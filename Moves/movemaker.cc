#include "movemaker.h"
#include <iostream>
using namespace std;

MoveMaker::MoveMaker(ChessBoard &b): board{b} { initBoardState(); }

void MoveMaker::initBoardState(Colour starting) {
    turn = starting;
    enPassant = std::nullopt;
    castlingRights = {
        {Colour::White, {{CastleType::KingSide, true}, {CastleType::QueenSide, true}}}, 
        {Colour::Black, {{CastleType::KingSide, true}, {CastleType::QueenSide, true}}}
    };
}

// assumes m is a legal move
void MoveMaker::makeMove(Move m, bool official) {
    previous.emplace_back(MoveData{m, BoardState{turn, enPassant, castlingRights}});

    // add and remove pieces.
    board.removePiece(m.getFrom(), official);
    if (m.isPromotion()) {
        board.setPiece(m.getTo(), m.getPromotionPiece(), official);
    } else {
        board.setPiece(m.getTo(), m.getPiece(), official);
    }

    // special cases.
    auto [r, c] = m.getFrom();
    auto [nr, nc] = m.getTo();
    if (m.isCastle()) {
        Tile oldRookTile = c < nc ? Tile{r, 7} : Tile{r, 0};
        Tile newRookTile{r, (c+nc)/2};
        board.setPiece(newRookTile, board.getPiece(oldRookTile), official);
        board.removePiece(oldRookTile, official);
    
    } else if (m.isEnPassant()) {
        Tile captureTile{r, nc};
        board.removePiece(captureTile, official);
    }

    // castling states.
    if (m.getPiece().isKing()) {
        castlingRights.at(turn).at(CastleType::KingSide) = false;
        castlingRights.at(turn).at(CastleType::QueenSide) = false;

    } else if (m.getPiece().isRook()) {
        if (m.getFrom().col == 0) {
            castlingRights.at(turn).at(CastleType::QueenSide) = false;
        } else if (m.getFrom().col == 7) {
            castlingRights.at(turn).at(CastleType::KingSide) = false;
        }
    }

    // en passant state.
    if (m.isDoubleAdvance()) {
        enPassant = m.getTo();
    } else {
        enPassant = nullopt;
    }

    // change turn
    turn = (turn == Colour::White) ? Colour::Black : Colour::White;
}

void MoveMaker::undoMove(bool official) {
    // get previous move.
    if (previous.size() == 0) return;
    MoveData lastMoveData = previous.back();
    Move lastMove = lastMoveData.move;

    Tile fromTile = lastMove.getFrom();
    Tile toTile = lastMove.getTo();
    previous.pop_back();

    // revert piece to original tile
    board.setPiece(fromTile, lastMove.getPiece(), official);
    board.removePiece(toTile, official);

    auto [r, c] = lastMove.getFrom();
    auto [nr, nc] = lastMove.getTo();

    if (lastMove.isCastle()){
        Tile oldRookTile = c < nc ? Tile{r, 7} : Tile{r, 0};
        Tile newRookTile{r, (c+nc)/2};
        board.setPiece(oldRookTile, board.getPiece(newRookTile), official);
        board.removePiece(newRookTile, official);

    } else if (lastMove.isEnPassant()) {
        Tile captureTile{r, nc};
        board.setPiece(captureTile, lastMove.getCapturePiece(), official);

    } else if (lastMove.isCapture()) {
        board.setPiece(toTile, lastMove.getCapturePiece(), official);
    }
    
    // reverting all invisible board states. (en passant/castling)
    BoardState lastState = lastMoveData.oldState;
    turn = lastState.turn;
    enPassant = lastState.enPassant;
    castlingRights = lastState.castlingRights;
}

// board state accessors.
Colour MoveMaker::getTurn() const noexcept { return turn; }
std::optional<Tile> MoveMaker::getEnPassant() const noexcept { return enPassant; }
std::map<Colour, std::map<CastleType, bool>> MoveMaker::getCastlingRights() const noexcept {
    return castlingRights;
}
bool MoveMaker::getCastlingRights(Colour c, CastleType s) const {
    return castlingRights.at(c).at(s);
}

// board state mutators.
void MoveMaker::setTurn(Colour c) { turn = c; }
void MoveMaker::setEnPassant(std::optional<Tile> t) { enPassant = t; }
void MoveMaker::setCastlingRights(std::map<Colour, std::map<CastleType, bool>> c) {
    castlingRights = c;
}
void MoveMaker::setCastlingRights(Colour c, CastleType s, bool b) {
    castlingRights.at(c).at(s) = b;
}
