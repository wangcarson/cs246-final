#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>

// errors
const int DEFAULT_ERROR = 0;
const int EOF_ERROR = 1;
const int RESIGN_ERROR = 2;

// this is low cohesion. move later (im too lazy rn)
enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty, Invalid };
enum class Mode { Setup, Game, Normal };
enum class Colour { White = 1, Black = -1, None = 0 };
enum class MoveType { Quiet, DoublePush, Castle, Capture, EnPassant, Promotion, PromotionCapture };

struct Tile {
    int row;
    int col;
    bool operator==(Tile t);
};

struct Piece { // change to class later
    PieceType type;
    Colour colour;

    bool isKing() { return type == PieceType::King; }
    bool isRook() { return type == PieceType::Rook; }
    // add more
};

// Helper functions
Piece parsePiece(std::string s);  // P, p, etc. to Piece()
Tile parseTile(std::string s);    // eg. from 'e3' to Tile(5, 2)

class Move {
    MoveType type;
    Tile startTile, endTile;
    Piece piece, capturePiece, promotionPiece; // optional

public:
    Move();
    Move(MoveType type, Tile from, Tile to);

    Colour getColour();
    MoveType getType();
    Tile getFrom();
    Tile getTo();
    Piece getPiece();
    Piece getCapturePiece();
    Piece getPromotionPiece();

    void setPiece(Piece p);
    void setCapturePiece(Piece p);
    void setPromotionPiece(Piece p);
    
    bool operator==(Move m);
    bool isCapture();
    bool isPromotion();
    bool isEnPassant();
    bool isCastle();
    bool isDoubleAdvance();
};

// keeps a move and previous state (for undoing moves)
struct TurnData {
    Colour turn;
    Move move;
    std::optional<Tile> enPassant; // nullopt to represent no tile
    std::map<Colour, bool> castlingRights;
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
