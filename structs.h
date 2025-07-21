#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>

// Board size constant
const int BOARD_ROWS = 8;
const int BOARD_COLS = 8;

// errors
class resign_error: public std::runtime_error {
  public:
    explicit resign_error(const std::string& msg = ""): runtime_error(msg) {}
};

class eof_error: public std::runtime_error {
  public:
    explicit eof_error(const std::string& msg = ""): runtime_error(msg) {}
};


////////////////////////////////////////////////////////////

enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty, Invalid };

enum class Mode { Setup, Game, Normal };
// Setup Mode is for when we are setting up a position.
// Game Mode is for taking move commands from input
// Normal Mode is defult before we choose what other mode we want to be in.

enum class Colour { White = 1, Black = -1, None = 0 };

enum class MoveType { Quiet, DoublePush, KingSideCastle, QueenSideCastle, Capture, EnPassant, Promotion, PromotionCapture };

////////////////////////////////////////////////////////////

struct Tile {
    int row;
    int col;
    bool operator==(const Tile &other) const {
        return row == other.row && col == other.col;
    }
    Tile operator+(const Tile &other) const {
    	return {row + other.row, col + other.col}; // can instead impl in terms of +=
    }
    Tile operator+=(const Tile &other) {
    	row += other.row;
    	col += other.col;
    	return *this;
    }
};

////////////////////////////////////////////////////////////

struct Piece {
    PieceType type;
    Colour colour;
    Tile position; // 

    bool isKing() { return type == PieceType::King; }
    bool isQueen() { return type == PieceType::Queen; }
    bool isRook() { return type == PieceType::Rook; }
    bool isBishop() { return type == PieceType::Bishop; }
    bool isKnight() { return type == PieceType::Knight; }
    bool isPawn() { return type == PieceType::Pawn; }
    bool isEmpty() { return type == PieceType::Empty; }
    bool isInvalid() { return type == PieceType::Invalid; }
    bool isColour(Colour c) { return colour == c; }

    bool operator<(const Piece& other) const {
        if (colour != other.colour)
            return colour < other.colour;
        return type < other.type;
    }
};

// Empty and invalid piece constants
const Piece EMPTY_PIECE{PieceType::Empty, Colour::None};
const Piece INVALID_PIECE{PieceType::Invalid, Colour::None};

// Parsing Pieces and Tiles
Tile parseTile(std::string s);
Piece parsePiece(char s);
char getPieceChar(Piece p);

// for debugging
std::ostream &operator<<(std::ostream &out, const Piece &p);

////////////////////////////////////////////////////////////

class Move {
    MoveType type;
    Piece piece, capturePiece, promotionPiece; // last two are optional
    Tile startTile, endTile;

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

////////////////////////////////////////////////////////////

// keeps a move and previous state (for undoing moves)
struct BoardState {
    Colour turn;
    Move move;
    std::optional<Tile> enPassant; // nullopt to represent no tile
    std::map<Colour, bool> castlingRights;
};

#endif
