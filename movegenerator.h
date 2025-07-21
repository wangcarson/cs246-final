#ifndef __MOVEGENERATOR_H__
#define __MOVEGENERATOR_H__

#include "structs.h"
#include "chessboard.h"

class MoveGenerator {
    ChessBoard &board;

    // add private functions
    // getPawnMoves(Tile t);

    std::vector<Move> pawnLegalGen(Tile t,Colour c);//need to know last move so that we can check for en passon
    std::vector<Move> rookLegalGen(Tile t,Colour c);
    std::vector<Move> queenLegalGen(Tile t,Colour c);
    std::vector<Move> knightLegalGen(Tile t,Colour c);
    std::vector<Move> bishopLegalGen(Tile t,Colour c);
    std::vector<Move> kingLegalGen(Tile t,Colour c); //need a way to check for castling

    //check castling seperalty
    //check en passon seperatly

  public:
    MoveGenerator(ChessBoard &b);

    // generating moves.
    std::vector<Move> generateLegalMoves(Colour c); //without castling or en passon.
    std::vector<Move> getLegalMoves(Tile t);
};

#endif
