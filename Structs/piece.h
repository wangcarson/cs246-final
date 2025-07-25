#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>

// custom enums for piece types and colours.
enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty };
enum class Colour { White = 1, Black = -1, None = 0 };

// Piece struct for storing a piece on a board.
struct Piece {
    PieceType type;
    Colour colour;

    bool isKing() const;
    bool isQueen() const;
    bool isRook() const;
    bool isBishop() const;
    bool isKnight() const;
    bool isPawn() const;
    bool isEmpty() const;

    bool isColour(Colour c) const;
    bool isOppositeColour(Colour c) const;

    // required for map
    bool operator==(const Piece& other) const;
    bool operator<(const Piece& other) const;
};

// empty piece constant.
const Piece EMPTY_PIECE{PieceType::Empty, Colour::None};

// helper functions with colours and pieces.
Colour oppositeColour(Colour c);
Piece parsePiece(char s);
char getPieceChar(Piece p);

// output operators.
std::ostream &operator<<(std::ostream &out, const Piece &p);
std::ostream &operator<<(std::ostream &out, const PieceType &p);
std::ostream &operator<<(std::ostream &out, const Colour &c);

#endif
