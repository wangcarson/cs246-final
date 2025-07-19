#include "chessboard.h"
#include <string>
#include <iostream>
using namespace std;

ChessBoard::ChessBoard():
    grid{vector<vector<Piece>>(BOARD_ROWS, vector<Piece>(BOARD_COLS, EMPTY_PIECE))} {}

void ChessBoard::setPiece(Tile t, Piece p) {
    grid[t.row][t.col] = p;
    notifyObservers(t);
}

void ChessBoard::removePiece(Tile t) {
    grid[t.row][t.col] = EMPTY_PIECE;
    notifyObservers(t);
}

void ChessBoard::clearGrid() {
    for (size_t i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < row.size(); ++j) {
            removePiece(Tile{static_cast<int>(i), static_cast<int>(j)});
        }
    }
}

Piece ChessBoard::getPiece(Tile t) {
    return grid[t.row][t.col];
}

bool ChessBoard::isOccupied(Tile t) {
    Piece p = grid[t.row][t.col];
    return !p.isEmpty() && !p.isInvalid();
}

Tile ChessBoard::getKing(Colour c) {
    for (size_t i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < row.size(); ++j) {
            auto piece = row[j];
            if (piece.isKing() && piece.isColour(c)) {
                return Tile{static_cast<int>(i), static_cast<int>(j)};
            }
        }
    }
    throw runtime_error("No king? lmao"); // todo: add exception handling
}

void ChessBoard::printSize(string s) { // debugging
    cout << &grid << " " << grid.size() << " " << grid[0].size() << " " << s << endl;
}