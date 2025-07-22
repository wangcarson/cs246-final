#include "structs.h"
#include <iostream>
using namespace std;

Move::Move() {}
Move::Move(MoveType type, Piece piece, Tile from, Tile to): 
    type{type}, piece{piece}, startTile{from}, endTile{to} {}

Tile Move::getFrom() const { return startTile; }
Tile Move::getTo() const { return endTile; }
Colour Move::getColour() const { return piece.colour; }
MoveType Move::getType() const { return type; }
Piece Move::getPiece() const { return piece; }
Piece Move::getCapturePiece() const { return capturePiece; }
Piece Move::getPromotionPiece() const { return promotionPiece; }
 
void Move::setCapturePiece(Piece p) {}
void Move::setPromotionPiece(Piece p) {}

bool Move::isCapture() const { return type == MoveType::Capture || type == MoveType::EnPassant || type == MoveType::PromotionCapture; }
bool Move::isPromotion() const { return type == MoveType::Promotion || type == MoveType::PromotionCapture; }
bool Move::isEnPassant() const { return type == MoveType::EnPassant; }
bool Move::isCastle() const { return type == MoveType::KingSideCastle || type == MoveType::QueenSideCastle; }
bool Move::isDoubleAdvance() const { return type == MoveType::DoublePush; }

////////////////// For parsing pieces

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
    {Piece{PieceType::Empty,  Colour::None},  ' '}, // for print only
};

// Helper functions
Tile parseTile(std::string s) {
    if (s.size() != 2 || s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8') {
        throw std::invalid_argument("parseTile: Invalid tile " + s);
    }
    int col = s[0] - 'a'; // 'a' is 0
    int row = s[1] - '1'; // '1' is 0
    return Tile{row, col};
}

Piece parsePiece(char s) {
    auto it = CHAR_PIECE_MAP.find(s);
    if (it == CHAR_PIECE_MAP.end()) {
        throw std::invalid_argument("parsePiece: Invalid piece " + s);
    }
    return it->second;
}

char getPieceChar(Piece p) {
    auto it = PIECE_CHAR_MAP.find(p);
    if (it == PIECE_CHAR_MAP.end()) {
        throw std::invalid_argument("getPieceChar: Invalid Piece object.");
    }
    return it->second;
}

// debugging
std::ostream &operator<<(std::ostream &out, const Piece &p) {
    std::string s = "";
    s += getPieceChar(p);
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Tile &t) {
    // Convert col: 0 → 'a', 1 → 'b', etc.
    out << static_cast<char>('a' + t.col) << (t.row + 1);
    return out;
}

std::ostream &operator<<(std::ostream &out, const Move &m) {
    out << m.getPiece() << " from " << m.getFrom() << " to " << m.getTo();
    if (m.isCapture()) { out << " capture " << m.getCapturePiece(); }
    if (m.isPromotion()) { out << " promote " << m.getPromotionPiece(); }
    if (m.isEnPassant()) { out << " en passant"; }
    if (m.isCastle()) { out << " castle"; }
    if (m.isDoubleAdvance()) { out << " double push"; }
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<Move> &v) {
    int n = 0;
    for (const auto &move : v) {
        ++n;
        out << n << ": " << move << endl;
    }
    return out;
}

