#ifndef __MOVE_C__
#define __MOVE_C__
#include <optional>
#include <map>
#include "structs.h"

class Move {
    MoveType type;
    Tile startTile, endTile;
    Piece piece, capturePiece, promotionPiece; // optional

  public:
    Move();
    Move(MoveType type, Piece piece, Tile from, Tile to);

    Tile getFrom();
    Tile getTo();
    Colour getColour();
    MoveType getType();
    Piece getPiece();
    Piece getCapturePiece();
    Piece getPromotionPiece();

    void setCapturePiece(Piece p);
    void setPromotionPiece(Piece p);
    
    bool isCapture();
    bool isPromotion();
    bool isEnPassant();
    bool isCastle();
    bool isDoubleAdvance();
};

#endif
