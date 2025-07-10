#include <string>
#include "board.h"

const std::string DEFAULT_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

void Board::init() {
    // initialize state
    turn = Colour::White;
    enPassant = std::nullopt;
    castleBlack = false;
    castleWhite = false;
    
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
            addPiece(PIECE_MAP.at(c), Tile{row, col});
        }
    }
}

void Board::addPiece(Piece p, Tile t) {
    position[t.row][t.col] = p;
    setState(t);
    notifyObservers();
}

void Board::removePiece(Tile t);
void Board::setTurn(Colour c);
Colour Board::getTurn();
bool Board::isValidBoard();
