#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <vector>

#include "piece.h"
#include "tile.h"
#include "subject.h"

class ChessBoard: public Subject {
    std::vector<std::vector<Piece>> grid;
    Colour turn;
  
  public:
    ChessBoard();

    // modifying the board.
    void setPiece(Tile t, Piece p, bool official=false);
    void removePiece(Tile t, bool official=false);
    void clearGrid();

    // board accessors.
    Piece getPiece(Tile t);
    Colour getColour(Tile t);
    bool isOccupied(Tile t);
    bool isEmpty(Tile t);
    Tile getKing(Colour c);
    Colour getTurn();
};

#endif
