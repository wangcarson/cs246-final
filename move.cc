#ifndef __MOVE_H__
#define __MOVE_H__
#include <optional>
#include <map>
#include "move.h"
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

void Move::setCapturePiece(Piece p){}

void Move::setPromotionPiece(Piece p){}

bool Move::isCapture(){}

bool Move::isPromotion(){}

bool Move::isEnPassant(){}

bool Move::isCastle(){}

bool Move::isDoubleAdvance(){}

#endif
