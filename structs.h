#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

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

enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty };

enum class Mode { Setup, Game, Normal };
// Setup Mode is for when we are setting up a position.
// Game Mode is for taking move commands from input
// Normal Mode is defult before we choose what other mode we want to be in.

enum class Colour { White = 1, Black = -1, None = 0 };
enum class CastleType { KingSide, QueenSide };

////////////////////////////////////////////////////////////

struct Tile {
    int row;
    int col;
    bool operator==(const Tile &other) const {
        return row == other.row && col == other.col;
    }
    Tile &operator+=(const Tile &other) {
        row += other.row;
    	col += other.col;
    	return *this;
    }
    Tile operator+(const Tile &other) const {
        Tile tmp{*this};
        return tmp += other;
    }
    bool inBoard() const {
        return col >= 0 && row >= 0 && col < BOARD_COLS && row < BOARD_ROWS; 
    }
};

////////////////////////////////////////////////////////////

struct Piece {
    PieceType type;
    Colour colour;
    // removed Tile

    bool isKing() const { return type == PieceType::King; }
    bool isQueen() const { return type == PieceType::Queen; }
    bool isRook() const { return type == PieceType::Rook; }
    bool isBishop() const { return type == PieceType::Bishop; }
    bool isKnight() const { return type == PieceType::Knight; }
    bool isPawn() const { return type == PieceType::Pawn; }
    bool isEmpty() const { return type == PieceType::Empty; }
    bool isColour(Colour c) const { return colour == c; }
    
    bool isOppositeColour(Colour c) const {
        switch (c) {
            case Colour::Black: return colour == Colour::White;
            case Colour::White: return colour == Colour::Black;
            default:
                throw std::invalid_argument("oppositeColour: Input colour must be White or Black");
        }
    }

    bool operator<(const Piece& other) const {
        if (colour != other.colour)
            return colour < other.colour;
        return type < other.type;
    }
};

// Empty and invalid piece constants
const Piece EMPTY_PIECE{PieceType::Empty, Colour::None};

// Parsing Pieces and Tiles
Tile parseTile(std::string s);
Piece parsePiece(char s);
char getPieceChar(Piece p);

////////////////////////////////////////////////////////////

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
};

////////////////////////////////////////////////////////////

// keeps a move and previous state (for undoing moves)
struct BoardState {
    Colour turn;
    std::optional<Tile> enPassant; // nullopt to represent no tile
    std::map<Colour, std::map<CastleType, bool>> castlingRights;
};

struct MoveData {
    Move move;
    BoardState oldState;
};

// debugging
std::ostream &operator<<(std::ostream &out, const Piece &p);
std::ostream &operator<<(std::ostream &out, const Tile &t);
std::ostream &operator<<(std::ostream &out, const Move &m);
std::ostream &operator<<(std::ostream &out, const std::vector<Move> &v);

#endif
