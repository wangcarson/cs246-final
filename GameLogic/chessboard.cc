#include "chessboard.h"
#include <string>
#include <iostream>
using namespace std;

ChessBoard::ChessBoard():
    grid{vector<vector<Piece>>(BOARD_SIZE, vector<Piece>(BOARD_SIZE, EMPTY_PIECE))} {}

// For consistency, the only methods that should directly
// access grid are these 2
Piece ChessBoard::getPiece(Tile t) { // O(1)
    try { return grid.at(t.row).at(t.col); }
    catch (std::out_of_range &r) {
        cerr << "getPiece(): Tile out of range: " << t.row << " " << t.col << endl;
        throw;
    }
}

void ChessBoard::setPiece(Tile t, Piece p, bool official) { // O(1)
    grid.at(t.row).at(t.col) = p;
    if (official) notifyObservers(t);
}

void ChessBoard::removePiece(Tile t, bool official) { // O(1)
    setPiece(t, EMPTY_PIECE, official);
}

Colour ChessBoard::getColour (Tile t) { // O(1)
    return getPiece(t).colour;
}

// other methods should call the three
void ChessBoard::clearGrid() {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        auto row = grid[i];
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            removePiece(Tile{static_cast<int>(i), static_cast<int>(j)}, true);
        }
    }
}

bool ChessBoard::isOccupied(Tile t) {
    return !getPiece(t).isEmpty();
}

bool ChessBoard::isEmpty(Tile t) {
    return getPiece(t).isEmpty();
}

Tile ChessBoard::getKing(Colour c) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
        	Tile t = Tile{static_cast<int>(i), static_cast<int>(j)}; // maybe add different ctor for Tile
            Piece p = getPiece(t);
            if (p.isKing() && p.isColour(c)) {
                return t;
            }
        }
    }
    throw runtime_error("No king? lmao");
    // this should never in theory happen
    // the exception is just to satisfy the compiler
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

Colour ChessBoard::getTurn(){
    return turn;
}

