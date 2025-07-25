#include "movemaker.h"
#include <iostream>
using namespace std;

MoveMaker::MoveMaker(ChessBoard &b): board{b} { initBoardState(); }

void MoveMaker::initBoardState(Colour starting) {
    turn = starting;
    enPassant = std::nullopt;
    castleRightWK = true;
    castleRightWQ = true;
    castleRightBK = true;
    castleRightBQ = true;
}

// assumes m is a legal move
void MoveMaker::makeMove(const Move &m, bool official) {
    Tile fromTile = m.getFrom();
    Tile toTile = m.getTo();
    Piece p = m.getPiece();

    // add and remove pieces.
    board.removePiece(fromTile, official);
    if (m.isPromotion()) {
        board.setPiece(toTile, m.getPromotionPiece(), official);
    } else {
        board.setPiece(toTile, p, official);
    }

    // special cases.
    auto [r, c] = fromTile;
    auto [nr, nc] = toTile;
    if (m.isCastle()) {
        Tile oldRookTile = c < nc ? Tile{r, BOARD_SIZE-1} : Tile{r, 0};
        Tile newRookTile{r, (c+nc)/2};
        board.setPiece(newRookTile, board.getPiece(oldRookTile), official);
        board.removePiece(oldRookTile, official);
    
    } else if (m.isEnPassant()) {
        Tile captureTile{r, nc};
        board.removePiece(captureTile, official);
    }

    // castling states.
    if (p.isKing()) {
        setCastlingRights(turn, false);

    } else if (p.isRook()) {
        if (c == 0) {
            setCastlingRights(turn, CastleType::QueenSide, false);
        } else if (c == BOARD_SIZE-1) {
            setCastlingRights(turn, CastleType::KingSide, false);
        }
    }

    // en passant state.
    if (m.isDoubleAdvance()) {
        enPassant = toTile;
    } else {
        enPassant = nullopt;
    }

    // change turn
    previous.emplace_back(MoveData{std::move(m), 
                          BoardState{turn, enPassant, castleRightWK, castleRightWQ, castleRightBK, castleRightBQ}});
    turn = (turn == Colour::White) ? Colour::Black : Colour::White;
}

void MoveMaker::undoMove(bool official) {
    // get previous move.
    if (previous.size() == 0) return;
    MoveData &lastMoveData = previous.back();
    Move &lastMove = lastMoveData.move;

    Tile fromTile = lastMove.getFrom();
    Tile toTile = lastMove.getTo();
    
    // revert piece to original tile
    board.setPiece(fromTile, lastMove.getPiece(), official);
    board.removePiece(toTile, official);

    auto [r, c] = fromTile;
    auto [nr, nc] = toTile;
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
    BoardState &lastState = lastMoveData.oldState;
    turn = lastState.turn;
    enPassant = lastState.enPassant;
    castleRightWK = lastState.castleRightWK;
    castleRightWQ = lastState.castleRightWQ;
    castleRightBK = lastState.castleRightBK;
    castleRightBQ = lastState.castleRightBQ;
    
    previous.pop_back();
}

// board state accessors.
Colour MoveMaker::getTurn() const noexcept { return turn; }
std::optional<Tile> MoveMaker::getEnPassant() const noexcept { return enPassant; }
bool MoveMaker::getCastlingRights(Colour c, CastleType s) const {
    if (c == Colour::White) {
        if (s == CastleType::KingSide) return castleRightWK;
        else return castleRightWQ;
    } else {
        if (s == CastleType::KingSide) return castleRightBK;
        else return castleRightBQ;
    }
}

// board state mutators.
void MoveMaker::setTurn(Colour c) { turn = c; }
void MoveMaker::setCastlingRights(Colour c, bool b) {
    if (c == Colour::White) {
        castleRightWK = b;
        castleRightWQ = b;
    } else {
        castleRightBK = b;
        castleRightBQ = b;
    }
}
void MoveMaker::setCastlingRights(Colour c, CastleType s, bool b) {
    if (c == Colour::White) {
        if (s == CastleType::KingSide) castleRightWK = b;
        else castleRightWQ = b;
    } else {
        if (s == CastleType::KingSide) castleRightBK = b;
        else castleRightBQ = b;
    }
}
