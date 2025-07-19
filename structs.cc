#include "structs.h"

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
