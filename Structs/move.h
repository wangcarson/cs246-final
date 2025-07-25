#ifndef __MOVE_H__
#define __MOVE_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include "piece.h"
#include "tile.h"

// custom exceptions.
class invalid_move: public std::exception {};
class puzzle_end: public std::exception {};
class illegal_move: public std::exception {};

// custom enums for representing type.
enum class MoveType { Quiet, DoublePush, KingSideCastle, QueenSideCastle, Capture, EnPassant, Promotion, PromotionCapture };
enum class CastleType { KingSide, QueenSide };

// Move class.
// Represents a single move and keeps necessary information for making and undoing the move.
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

// Keeps a move and previous state.
// Used by MoveMaker for storing data to undo moves.
struct BoardState {
    Colour turn;
    std::optional<Tile> enPassant; // nullopt to represent no tile
    std::map<Colour, std::map<CastleType, bool>> castlingRights;
};
struct MoveData {
    Move move;
    BoardState oldState;
};

// output operators.
std::ostream &operator<<(std::ostream &out, const Move &m);
std::ostream &operator<<(std::ostream &out, const std::vector<Move> &v);

#endif
