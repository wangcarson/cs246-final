#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>
#include "move.h"

// errors
const int DEFAULT_ERROR = 0;
const int EOF_ERROR = 1;
const int RESIGN_ERROR = 2;

enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty, Invalid };
enum class Mode { Setup, Game, Normal };
// Setup Mode is for when we are setting up a position.
// Game Mode is for taking move commands from input
// Normal Mode is defult before we choose what other mode we want to be in.

enum class Colour { White = 1, Black = -1, None = 0 };
enum class MoveType { Quiet, DoublePush, KingSideCastle,QueenSideCastle, Capture, EnPassant, Promotion, PromotionCapture };

////////////////////////////////////////////////////////////

struct Tile {
    int row;
    int col;
    bool operator==(Tile t);
};

////////////////////////////////////////////////////////////

struct Piece { // change to class later
    PieceType type;
    Colour colour;
    Tile position;

    bool isKing() { return type == PieceType::King; }
    bool isQueen() { return type == PieceType::Queen; }
    bool isRook() { return type == PieceType::Rook; }
    bool isBishop() { return type == PieceType::Bishop; }
    bool isKnight() { return type == PieceType::Knight; }
    bool isPawn() { return type == PieceType::Pawn; }
    bool isEmpty() { return type == PieceType::Empty; }
    bool isInvalid() { return type == PieceType::Invalid; }
    bool isWhite() { return colour == Colour::White; }

    Colour getColour(){
        return colour;
    }
    Tile getTile(){
        return position;
    }

    // add more
};

// Helper functions
Piece parsePiece(std::string s);  // P, p, etc. to Piece()
Tile parseTile(std::string s);    // eg. from 'e3' to Tile(5, 2)

////////////////////////////////////////////////////////////

// keeps a move and previous state (for undoing moves)
struct BoardState {
    Colour turn;
    std::optional<Tile> enPassant; // nullopt to represent no tile
    Move move;
    bool castleKingWhite;
    bool castleQueenBlack;
    bool castleQueenWhite;
    bool castleKingBlack;
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
