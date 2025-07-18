#include <string>
#include "chessBoard.h"
using namespace std;

void ChessBoard::setPiece(Tile t, Piece p) {
    grid[t.row][t.col] = p;
    notifyObservers(t);
}

void ChessBoard::removePiece(Tile t) {
    grid[t.row][t.col] = nullopt;
    notifyObservers(t);
}

void ChessBoard::clearGrid() {
    // todo
}

bool isOccupied(Tile t) {
    // todo
}

Piece getPiece(Tile t) {
    // todo
}

Tile ChessBoard::getKing(Colour c) {
    // todo
}
