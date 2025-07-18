#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <vector>
#include <optional>

#include "structs.h"
#include "subject.h"

class ChessBoard: public Subject {
    std::vector<std::vector<std::optional<Piece>>> position;
  
  public:
    ChessBoard();
    
    // changing board. (should call observers)
    void setPiece(Tile t, Piece p);
    void removePiece(Tile t);

    // some accessors.
    bool isOccupied(Tile t);
    Piece getPiece(Tile t);
    Tile getKing(Colour c);
};

#endif
