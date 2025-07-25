#ifndef __MOVE_H__
#define __MOVE_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include "structs.h"


enum class MoveType { Quiet, DoublePush, KingSideCastle, QueenSideCastle, Capture, EnPassant, Promotion, PromotionCapture };

class Move {
    MoveType type;
    Piece piece, capturePiece, promotionPiece; // last two are optional
    Tile startTile, endTile;

  public:
    Move();
    Move(MoveType type, Piece piece, Tile from, Tile to);

    Tile getFrom() const;
    Tile getTo() const;
    Colour getColour() const;
    MoveType getType() const;
    Piece getPiece() const;
    Piece getCapturePiece() const;
    Piece getPromotionPiece() const;

    void setCapturePiece(Piece p);
    void setPromotionPiece(Piece p);
    
    bool isCapture() const;
    bool isPromotion() const;
    bool isEnPassant() const;
    bool isCastle() const;
    bool isDoubleAdvance() const;
    bool isQCastle() const;
    bool isKCastle() const;
};

std::ostream &operator<<(std::ostream &out, const Move &m);
std::ostream &operator<<(std::ostream &out, const std::vector<Move> &v);

#endif