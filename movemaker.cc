#include "movemaker.h"
#include <iostream>
using namespace std;

MoveMaker::MoveMaker(ChessBoard &b): board{b} { initBoardState(); }

void MoveMaker::initBoardState() {
    turn = Colour::White;
    enPassant = std::nullopt;
    castlingRights = {
        {Colour::White, {{CastleType::KingSide, true}, {CastleType::QueenSide, true}}}, 
        {Colour::Black, {{CastleType::KingSide, true}, {CastleType::QueenSide, true}}}
    };
}

// assumes m is a legal move
void MoveMaker::makeMove(Move m) {
    cout << "Move: ";
    previous.emplace_back(MoveData{m, BoardState{turn, enPassant, castlingRights}});

    // add and remove pieces.
    board.removePiece(m.getFrom());
    if (m.isPromotion()) {
        cout << "Promotion." << endl;
        board.setPiece(m.getTo(), m.getPromotionPiece());
    } else {
        board.setPiece(m.getTo(), m.getPiece());
    }

    // special cases.
    auto [r, c] = m.getFrom();
    auto [nr, nc] = m.getTo();
    if (m.isCastle()) {
        cout << "Castle." << endl;
        Tile oldRookTile = c < nc ? Tile{r, 7} : Tile{r, 1};
        Tile newRookTile{r, (c+nc)/2};
        board.removePiece(oldRookTile);
        board.setPiece(newRookTile, Piece{PieceType::Rook, turn});
    
    } else if (m.isEnPassant()) {
        cout << "En Passant." << endl;
        Tile captureTile{r, nc};
        board.removePiece(captureTile);
    }

    // castling states.
    if (m.getPiece().isKing()) {
        cout << "King moved. No castling" << endl;
        castlingRights.at(turn).at(CastleType::KingSide) = false;
        castlingRights.at(turn).at(CastleType::QueenSide) = false;

    } else if (m.getPiece().isRook()) {
        cout << "Rook moved. No castling" << endl;
        if (m.getTo().col == 0) {
            castlingRights.at(turn).at(CastleType::QueenSide) = false;
        } else if (m.getTo().col == 7) {
            castlingRights.at(turn).at(CastleType::KingSide) = false;
        }
    }

    // en passant state.
    if (m.isDoubleAdvance()) {
        cout << "Double push." << endl;
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
bool MoveMaker::getCastlingRights(Colour c, CastleType s) {
    return castlingRights.at(c).at(s);
}

// board state mutators.
void MoveMaker::setTurn(Colour c) { turn = c; }
void MoveMaker::setEnPassant(std::optional<Tile> t) { enPassant = t; }
void MoveMaker::setCastlingRights(Colour c, CastleType s, bool b) {
    castlingRights.at(c).at(s) = b;
}
