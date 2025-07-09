#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>

// this is low cohesion. move later (im too lazy rn)
enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen };
enum class Mode { Setup, Game, Normal };
enum class Colour { Black, White };
enum class MoveType { Promotion, PromotionCapture, EnPassant, Capture, Castle, Regular, Unknown };

struct Tile {
    int row;
    int col;
};

struct Piece { // change to class later
    PieceType type;
    Colour colour;
};

struct Move {
    MoveType type;
    Tile startTile;
    Tile endTile;
    std::optional<Tile> captureTile = std::nullopt; // for en passant
};

const std::map<char, Piece> PIECE_MAP = {
    {'P', Piece{PieceType::Pawn,   Colour::White}},
    {'N', Piece{PieceType::Knight, Colour::White}},
    {'B', Piece{PieceType::Bishop, Colour::White}},
    {'R', Piece{PieceType::Rook,   Colour::White}},
    {'Q', Piece{PieceType::Queen,  Colour::White}},
    {'K', Piece{PieceType::King,   Colour::White}},
    {'p', Piece{PieceType::Pawn,   Colour::Black}},
    {'n', Piece{PieceType::Knight, Colour::Black}},
    {'b', Piece{PieceType::Bishop, Colour::Black}},
    {'r', Piece{PieceType::Rook,   Colour::Black}},
    {'q', Piece{PieceType::Queen,  Colour::Black}},
    {'k', Piece{PieceType::King,   Colour::Black}}
};

#endif
