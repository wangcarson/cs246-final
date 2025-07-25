#include "move.h"
using namespace std;

Move::Move() {}
Move::Move(MoveType type, Piece piece, Tile from, Tile to): 
    type{type}, piece{piece}, startTile{from}, endTile{to} {}

Tile Move::getFrom() const { return startTile; }
Tile Move::getTo() const { return endTile; }
Colour Move::getColour() const { return piece.colour; }
MoveType Move::getType() const { return type; }
Piece Move::getPiece() const { return piece; }
Piece Move::getCapturePiece() const {
    return capturePiece;
}
Piece Move::getPromotionPiece() const {
    return promotionPiece; 
}
 
void Move::setCapturePiece(Piece p) { capturePiece = p; }
void Move::setPromotionPiece(Piece p) { promotionPiece = p; }

bool Move::isCapture() const { return type == MoveType::Capture || type == MoveType::EnPassant || type == MoveType::PromotionCapture; }
bool Move::isPromotion() const { return type == MoveType::Promotion || type == MoveType::PromotionCapture; }
bool Move::isEnPassant() const { return type == MoveType::EnPassant; }
bool Move::isCastle() const { return type == MoveType::KingSideCastle || type == MoveType::QueenSideCastle; }
bool Move::isQCastle() const { return type == MoveType::QueenSideCastle; }
bool Move::isKCastle() const { return type == MoveType::KingSideCastle; }

bool Move::isDoubleAdvance() const { return type == MoveType::DoublePush; }

std::ostream &operator<<(std::ostream &out, const Move &m) {
    out << m.getPiece() << " from " << m.getFrom() << " to " << m.getTo();
    if (m.isEnPassant()) { out << " en passant"; }
    if (m.isCapture()) { out << " capture " << m.getCapturePiece(); }
    if (m.isPromotion()) { out << " promote " << m.getPromotionPiece(); }
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
