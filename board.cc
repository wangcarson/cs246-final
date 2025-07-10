#include <string>
#include "board.h"
using namespace std;

const int BOARD_SIZE = 8;
const std::string DEFAULT_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

void Board::init() {
    // initialize state
    turn = Colour::White;
    enPassant = nullopt;
    castlingRights = {{Colour::White, false}, {Colour::Black, false}};

    // initialize grid to default (import FEN)
    position.clear();
    int row = 0, col = 0;
    for (char c : DEFAULT_POSITION) {
        if (c == '/') {
            row++;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            setPiece(Tile{row, col}, PIECE_MAP.at(c));
        }
    }
}

void Board::setTurn(Colour c) { turn = c; }
Colour Board::getTurn() { return turn; }

void Board::setPiece(Tile t, Piece p) {
    position[t.row][t.col] = p;
    notifyObservers(t);
}
void Board::removePiece(Tile t) {
    position[t.row][t.col] = nullopt;
    notifyObservers(t);
}

bool Board::isValidBoard() {
    // todo
}

bool Board::isLegal(Move m) {
    makeMove(m);
    bool legal = !isCheck(m.getColour());
    undoMove(m);
    return legal;
}

void Board::makeMove(Move m) {
    // add and remove pieces.
    removePiece(m.getFrom());
    if (m.isPromotion()) {
        setPiece(m.getTo(), m.getPromotionPiece());
    } else {
        setPiece(m.getTo(), m.getPiece());
    }
    // special cases.
    auto [r, c] = m.getFrom();
    auto [nr, nc] = m.getTo();
    if (m.isCastle()) {
        Tile oldRookTile = c < nc ? Tile{r, 7} : Tile{r, 1};
        Tile newRookTile{r, (c+nc)/2};
        removePiece(oldRookTile);
        setPiece(newRookTile, Piece{PieceType::Rook, turn});

    } else if (m.isEnPassant()) {
        Tile captureTile{r, nc};
        removePiece(captureTile);
    }
    // castling rights.
    if (m.getPiece().isRook() || m.getPiece().isKing()) {
        castlingRights[turn] = false;
    }
    // en passant state.
    if (m.isDoubleAdvance()) {
        enPassant = m.getTo();
    } else {
        enPassant = nullopt;
    }
    previousMoves.emplace_back(TurnData{turn, m, enPassant, castlingRights});
    turn = turn == Colour::White ? Colour::Black : Colour::White;
}

void Board::undoMove(Move m) {
    // todo
}