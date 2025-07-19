#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>

// errors
const int DEFAULT_ERROR = 0;
const int EOF_ERROR = 1;
const int RESIGN_ERROR = 2;

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

const std::map<char, Piece> CHAR_PIECE_MAP = { // for creating pieces
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

const std::map<Piece, char> PIECE_CHAR_MAP = {
    {Piece{PieceType::Pawn,   Colour::White}, 'P'},
    {Piece{PieceType::Knight, Colour::White}, 'N'},
    {Piece{PieceType::Bishop, Colour::White}, 'B'},
    {Piece{PieceType::Rook,   Colour::White}, 'R'},
    {Piece{PieceType::Queen,  Colour::White}, 'Q'},
    {Piece{PieceType::King,   Colour::White}, 'K'},
    {Piece{PieceType::Pawn,   Colour::Black}, 'p'},
    {Piece{PieceType::Knight, Colour::Black}, 'n'},
    {Piece{PieceType::Bishop, Colour::Black}, 'b'},
    {Piece{PieceType::Rook,   Colour::Black}, 'r'},
    {Piece{PieceType::Queen,  Colour::Black}, 'q'},
    {Piece{PieceType::King,   Colour::Black}, 'k'}
};

// Helper functions
Tile parseTile(std::string s) {
    if (s.size() != 2 || s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8') {
        throw std::invalid_argument("Invalid tile string: " + s);
    }
    int col = s[0] - 'a'; // 'a' → 0, ..., 'h' → 7
    int row = s[1] - '1'; // '1' → 0, ..., '8' → 7
    return Tile{row, col};
}

Piece parsePiece(char s) {
    auto it = CHAR_PIECE_MAP.find(s);
    if (it == CHAR_PIECE_MAP.end()) {
        throw std::invalid_argument("parsePiece: Invalid piece character: " + s);
    }
    return it->second;
}

char getPieceChar(Piece p) {
    auto it = PIECE_CHAR_MAP.find(p);
    if (it == PIECE_CHAR_MAP.end()) {
        throw std::invalid_argument("getPieceChar: Invalid piece");
    }
    return it->second;
}

#endif
