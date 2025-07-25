#include "piece.h"
#include <map>

// Piece methods.
bool Piece::isKing() const { return type == PieceType::King; }
bool Piece::isQueen() const { return type == PieceType::Queen; }
bool Piece::isRook() const { return type == PieceType::Rook; }
bool Piece::isBishop() const { return type == PieceType::Bishop; }
bool Piece::isKnight() const { return type == PieceType::Knight; }
bool Piece::isPawn() const { return type == PieceType::Pawn; }
bool Piece::isEmpty() const { return type == PieceType::Empty; }

bool Piece::isColour(Colour c) const { return colour == c; }
bool Piece::isOppositeColour(Colour c) const { return colour == oppositeColour(c); }

// required for map
bool Piece::operator==(const Piece& other) const {
    return (colour == other.colour) && (type == other.type);
}
bool Piece::operator<(const Piece& other) const {
    if (colour != other.colour)
        return colour < other.colour;
    return type < other.type;
}

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
    {Piece{PieceType::King,   Colour::Black}, 'k'},
    {Piece{PieceType::Empty,  Colour::None},  ' '} // for print only
};

// Parsing functions.
Piece parsePiece(char s) {
    auto it = CHAR_PIECE_MAP.find(s);
    if (it == CHAR_PIECE_MAP.end()) {
        throw std::invalid_argument("parsePiece(): Invalid piece.");
    }
    return it->second;
}

char getPieceChar(Piece p) {
    auto it = PIECE_CHAR_MAP.find(p);
    if (it == PIECE_CHAR_MAP.end()) {
        throw std::invalid_argument("getPieceChar(): Invalid Piece object.");
    }
    return it->second;
}

Colour oppositeColour(Colour c) {
    switch (c) {
        case Colour::Black: return Colour::White;
        case Colour::White: return Colour::Black;
        default:
            throw std::invalid_argument("oppositeColour(): Input colour must be White or Black.");
    }
}

std::ostream &operator<<(std::ostream &out, const PieceType &p) {
    if (p == PieceType::Bishop) out << "bishop";
    else if (p == PieceType::Rook) out << "rook";
    else if (p == PieceType::Knight) out << "knight";
    else if (p == PieceType::King) out << "king";
    else if (p == PieceType::Queen) out << "queen";
    else if (p == PieceType::Pawn) out << "pawn";
    else if (p == PieceType::Empty) out << "empty";
    else out << "Invalid piece type.";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Colour &c) {
    if (c == Colour::White) out << "White";
    else if (c == Colour::Black) out << "Black";
    else if (c == Colour::None) out << "None";
    else out << "Invalid colour.";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Piece &p) {
    std::string s = "";
    s += getPieceChar(p);
    out << s;
    return out;
}
