#include "structs.h"
#include <iostream>
using namespace std;

Move::Move() {}
Move::Move(MoveType type, Piece piece, Tile from, Tile to): 
    type{type}, piece{piece}, startTile{from}, endTile{to} {}

Tile Move::getTo() { return startTile; }
Tile Move::getFrom() { return endTile; }
Colour Move::getColour() { return piece.colour; }
MoveType Move::getType() { return type; }
Piece Move::getPiece() { return piece; }
Piece Move::getCapturePiece() { return capturePiece; }
Piece Move::getPromotionPiece() { return promotionPiece; }

void Move::setCapturePiece(Piece p) {}
void Move::setPromotionPiece(Piece p) {}

bool Move::isCapture() { return type == MoveType::Capture || type == MoveType::EnPassant || type == MoveType::PromotionCapture; }
bool Move::isPromotion() { return type == MoveType::Promotion || type == MoveType::PromotionCapture; }
bool Move::isEnPassant() { return type == MoveType::EnPassant; }
bool Move::isCastle() { return type == MoveType::KingSideCastle || type == MoveType::QueenSideCastle; }
bool Move::isDoubleAdvance() { return type == MoveType::DoublePush; }

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
        // cerr << "Invalid tile: " + s;
        throw std::invalid_argument("Invalid tile.");
    }
    int col = s[0] - 'a'; // 'a' → 0, ..., 'h' → 7
    int row = s[1] - '1'; // '1' → 0, ..., '8' → 7
    return Tile{row, col};
}

Piece parsePiece(char s) {
    auto it = CHAR_PIECE_MAP.find(s);
    if (it == CHAR_PIECE_MAP.end()) {
        // cerr << "parsePiece: Invalid piece: " + s;
        throw std::invalid_argument("parsePiece: Invalid piece.");
    }
    return it->second;
}

char getPieceChar(Piece p) {
    auto it = PIECE_CHAR_MAP.find(p);
    if (it == PIECE_CHAR_MAP.end()) {
        // cerr << "getPieceChar: Invalid Piece object" << endl;
        throw std::invalid_argument("getPieceChar: Invalid Piece object.");
    }
    return it->second;
}

std::ostream &operator<<(std::ostream &out, const Piece &p) {
    std::string s = "";
    s += getPieceChar(p);
    out << s;
    return out;
}
