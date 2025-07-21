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

// other methods should call the three
void ChessBoard::clearGrid() {
    for (size_t i = 0; i < BOARD_ROWS; ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < BOARD_COLS; ++j) {
            removePiece(Tile{static_cast<int>(i), static_cast<int>(j)});
        }
    }
}

Piece ChessBoard::getPiece(Tile t) {
    return grid[t.row][t.col];
}

//colour accesor method
Colour ChessBoard::getColour (Tile t){
    return grid[t.row][t.col].colour;
}


bool ChessBoard::isOccupied(Tile t) {
    Piece p = getPiece(t);
    return !p.isEmpty() && !p.isInvalid();
}

Tile ChessBoard::getKing(Colour c) {
    for (size_t i = 0; i < BOARD_ROWS; ++i) {
        for (size_t j = 0; j < BOARD_COLS; ++j) {
        	Tile t = Tile{static_cast<int>(i), static_cast<int>(j)}; // maybe add different ctor for Tile
            Piece p = getPiece(t);
            if (p.isKing() && p.isColour(c)) {
                return t;
            }
        }
    }
    throw runtime_error("No king? lmao"); // todo: add exception handling
    //could return tile -1,-1? and we then would know that the king isn't on the board.
}

void ChessBoard::printSize(string s) { // debugging
    cout << &grid << " " << grid.size() << " " << grid[0].size() << " " << s << endl;
    for (auto r : grid) {
    	for (auto p : r) {
    		char ch = getPieceChar(p);
    		cout << ch;
    	}
    	cout << endl;
    }
}

