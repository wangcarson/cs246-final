#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>

// errors
const int EOF_ERROR = 1;
const int RESIGN_ERROR = 0;

// this is low cohesion. move later (im too lazy rn)
enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty, Invalid };
enum class Mode { Setup, Game, Normal };
enum class Colour { Black, White, None };
enum class MoveType { Quiet, DoublePush, Castle, Capture, EnPassant, Promotion, PromotionCapture };

struct Tile {
    int row;
    int col;
    bool operator==(Tile t);
};

struct Piece { // change to class later
    PieceType type;
    Colour colour;
};

// Helper functions
Piece parsePiece(std::string s);  // P, p, etc. to Piece()
Tile parseTile(std::string s);    // eg. from 'e3' to Tile(5, 2)

class Move {
    MoveType type;
    Tile startTile, endTile;
    Piece piece, capturePiece, promotionPiece;

public:
    Move();
    Move(MoveType type, Tile from, Tile to);

    MoveType getType();
    Tile getTo();
    Tile getFrom();
    Piece getPiece();
    Piece getCapturePiece();
    Piece getPromotionPiece();

    void setPiece(Piece p);
    void setCapturePiece(Piece p);
    void setPromotionPiece(Piece p);
    
    bool operator==(Move m);
    bool isCapture();
    bool isPromotion();
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
