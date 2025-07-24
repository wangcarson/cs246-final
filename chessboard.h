#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <vector>

#include "structs.h"
#include "subject.h"

class ChessBoard: public Subject {
    std::vector<std::vector<Piece>> grid;
    Colour turn;
  
  public:
    ChessBoard();

    // changing board. (should call observers)
    void setPiece(Tile t, Piece p);
    void removePiece(Tile t);
    void clearGrid();

    // some accessors.
    Piece getPiece(Tile t);
    Colour getColour(Tile t);
    bool isOccupied(Tile t);
    bool isEmpty(Tile t);
    Tile getKing(Colour c);

    void printSize(std::string s);
    Colour getTurn();
};

#endif
