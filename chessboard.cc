#include "chessboard.h"
#include <string>
using namespace std;

ChessBoard::ChessBoard():
grid{vector<vector<optional<Piece>>>(8, vector<optional<Piece>>(8, nullopt))} {}

void ChessBoard::setPiece(Tile t, Piece p) {
    grid[t.row][t.col] = p;
    notifyObservers(t);
}

void ChessBoard::removePiece(Tile t) {
    grid[t.row][t.col] = nullopt;
    notifyObservers(t);
}

void ChessBoard::clearGrid() {
    for (size_t i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < row.size(); ++j) {
            removePiece(Tile{(int)i, (int)j});
        }
    }
}

bool ChessBoard::isOccupied(Tile t) {
    return grid[t.row][t.col].has_value();
}

Piece ChessBoard::getPiece(Tile t) {
    if (!isOccupied(t)) {
        throw DEFAULT_ERROR; // todo: add exception handling
    }
    return grid[t.row][t.col].value();
}

Tile ChessBoard::getKing(Colour c) {
    for (size_t i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < row.size(); ++j) {
            auto piece = row[j];
            if (piece.has_value() && piece.value().isKing() && piece.value().isColour(c)) {
                return Tile{(int)i, (int)j};
            }
        }
    }
    throw DEFAULT_ERROR; // todo: add exception handling
}
