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
    // loop through pieces:
    // if pawn: check none on rank 0 or 7
    // if king: ensure one king of each colour
    // check isCheck(Colour::White) and isCheck(Colour::Black)
}

bool Board::isLegal(Move m) {
    makeMove(m);
    bool legal = !isCheck(m.getColour());
    undoMove();
    return legal;
}

// assumes m is a legal move
void Board::makeMove(Move m) {
    previousMoves.emplace_back(TurnData{turn, m, enPassant, castlingRights});

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

void Board::undoMove() {
    if (previousMoves.size() == 0) return;
    // set previous state to current state
    // move piece back
    // revert captured pieces
    // change turn
}

std::vector<Move> Board::generateMoves(Colour c) {
    // todo
}

Tile Board::getKing(Colour c) {
    // todo
}

bool Board::isCheck(Colour c) {
    Tile ktile = getKing(c);
    // check if opponent rook on same rank/file
    // bishop on diagonal
    // similar to move generation 
}

// check if *current* colour is in check
bool Board::isMate() {
    return isCheck(turn) && generateMoves(turn).size() == 0;
}

bool Board::isDraw() {
    return !isCheck(turn) && generateMoves(turn).size() == 0;
    // todo: check for insufficient material
}
