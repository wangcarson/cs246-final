#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <optional>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include "move.h"

// board size constants.
const int BOARD_SIZE = 8;

// new exception classes.
class invalid_move: public std::exception {};
class puzzle_end: public std::exception {};
class illegal_move: public std::exception {};
class tile_out_of_board: public std::out_of_range {
    public:
        tile_out_of_board(const std::string &s): out_of_range(s) {}
};

////////////////////////////////////////////////////////////

enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty };

enum class Colour { White = 1, Black = -1, None = 0 };
Colour oppositeColour(Colour c);

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
        return col >= 0 && row >= 0 && col < BOARD_SIZE && row < BOARD_SIZE; 
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
    bool isOppositeColour(Colour c) const { return colour == oppositeColour(c); }

    bool operator==(const Piece& other) const {
        return (colour == other.colour) && (type == other.type);
    }
    // required for map
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
std::ostream &operator<<(std::ostream &out, const PieceType &p);
std::ostream &operator<<(std::ostream &out, const Colour &c);

std::ostream &operator<<(std::ostream &out, const Piece &p);
std::ostream &operator<<(std::ostream &out, const Tile &t);


#endif
